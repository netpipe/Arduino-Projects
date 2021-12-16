#include "MPU6050_tockn-swire.h"
#include "Arduino.h"
#include "SWire.h"

MPU6050::MPU6050(){
  //wire = &w;
  accCoef = 0.02f;
  gyroCoef = 0.98f;
}

MPU6050::MPU6050(float aC, float gC){
 // wire = &w;
  accCoef = aC;
  gyroCoef = gC;
}

void MPU6050::begin(int sda1,int scl1,int addr){
if (addr == 1){
MPU6050_ADDR=0x68;
}else{
MPU6050_ADDR=0x69;
}
  SWire.begin(sda1,scl1);
  writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
  writeMPU6050(MPU6050_CONFIG, 0x00);
  writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
  writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
  writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
  this->update();
  angleGyroX = 0;
  angleGyroY = 0;
  angleX = this->getAccAngleX();
  angleY = this->getAccAngleY();
  preInterval = millis();
}

void MPU6050::writeMPU6050(byte reg, byte data){
  SWire.beginTransmission(MPU6050_ADDR);
  SWire.write(reg);
  SWire.write(data);
  SWire.endTransmission();
}

byte MPU6050::readMPU6050(byte reg) {
  SWire.beginTransmission(MPU6050_ADDR);
  SWire.write(reg);
  SWire.endTransmission(true);
  SWire.requestFrom(MPU6050_ADDR, 1);
  byte data =  SWire.read();
  return data;
}

void MPU6050::setGyroOffsets(float x, float y, float z){
  gyroXoffset = x;
  gyroYoffset = y;
  gyroZoffset = z;
}

void MPU6050::calcGyroOffsets(bool console, uint16_t delayBefore, uint16_t delayAfter){
	float x = 0, y = 0, z = 0;
	int16_t rx, ry, rz;

  delay(delayBefore);
	if(console){
    Serial.println();
    Serial.println("========================================");
    Serial.println("Calculating gyro offsets");
    Serial.print("DO NOT MOVE MPU6050");
  }
  for(int i = 0; i < 3000; i++){
    if(console && i % 1000 == 0){
      Serial.print(".");
    }
    SWire.beginTransmission(MPU6050_ADDR);
    SWire.write(0x43);
    SWire.endTransmission(false);
    SWire.requestFrom((int)MPU6050_ADDR, 6);

    rx =  SWire.read() << 8 |  SWire.read();
    ry = SWire.read() << 8 |  SWire.read();
    rz =  SWire.read() << 8 |  SWire.read();

    x += ((float)rx) / 65.5;
    y += ((float)ry) / 65.5;
    z += ((float)rz) / 65.5;
  }
  gyroXoffset = x / 3000;
  gyroYoffset = y / 3000;
  gyroZoffset = z / 3000;

  if(console){
    Serial.println();
    Serial.println("Done!");
    Serial.print("X : ");Serial.println(gyroXoffset);
    Serial.print("Y : ");Serial.println(gyroYoffset);
    Serial.print("Z : ");Serial.println(gyroZoffset);
    Serial.println("Program will start after 3 seconds");
    Serial.print("========================================");
		delay(delayAfter);
	}
}

void MPU6050::update(){
	SWire.beginTransmission(MPU6050_ADDR);
	SWire.write(0x3B);
	SWire.endTransmission(false);
	SWire.requestFrom((int)MPU6050_ADDR, 14);

  rawAccX =  SWire.read() << 8 |  SWire.read();
  rawAccY =  SWire.read() << 8 |  SWire.read();
  rawAccZ =  SWire.read() << 8 |  SWire.read();
  rawTemp =  SWire.read() << 8 |  SWire.read();
  rawGyroX =  SWire.read() << 8 |  SWire.read();
  rawGyroY =  SWire.read() << 8 |  SWire.read();
  rawGyroZ =  SWire.read() << 8 |  SWire.read();

  temp = (rawTemp + 12412.0) / 340.0;

  accX = ((float)rawAccX) / 16384.0;
  accY = ((float)rawAccY) / 16384.0;
  accZ = ((float)rawAccZ) / 16384.0;

  angleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 360 / 2.0 / PI;
  angleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 360 / -2.0 / PI;

  gyroX = ((float)rawGyroX) / 65.5;
  gyroY = ((float)rawGyroY) / 65.5;
  gyroZ = ((float)rawGyroZ) / 65.5;

  gyroX -= gyroXoffset;
  gyroY -= gyroYoffset;
  gyroZ -= gyroZoffset;

  interval = (millis() - preInterval) * 0.001;

  angleGyroX += gyroX * interval;
  angleGyroY += gyroY * interval;
  angleGyroZ += gyroZ * interval;

  angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
  angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
  angleZ = angleGyroZ;

  preInterval = millis();

}
