
#include <MPU6050_tockn-swire.h>

MPU6050 mpu6050();

void setup() {
  Serial.begin(9600);
  mpu6050.begin(A3,A4);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
}
