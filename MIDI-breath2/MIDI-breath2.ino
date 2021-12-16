// v2 MIDI breath controller -- with GYRO and microphone support


// needs leonardo or something with HID support to work properly
#define USBHID
#ifdef USBHID
    #include "MIDIUSB.h"
#endif

#define PLAY
//#define debug1
#define PRINTS

byte note = 0;
int hits;
unsigned long startMillis;
long elapsedmilis = 0;

const int OUT_PIN = 3; // digital pin for microphone.

#ifdef memory
#include <EEPROM.h>
int addr = 0;
#endif


#define MIDI_ON 144
#define MIDI_OFF 128

int samplebuffer = 0;

const int sampleWindow = 28; // Sample window width in mS (50 mS = 20Hz)
const int threshold1 = 26800;    // 350 higher value for larger sample window
const int threshold2 = 27000;
//const int threshold4 = 140; 
const int threshold3 = 28000; //rename to 4 after
int count = 0;

//#define GYRO
#ifdef GYRO
#include <MPU6050_tockn-swire.h>
MPU6050 mpu6050;
#endif

#include <SWire.h>
#include <Adafruit_BMP085-swire.h>

Adafruit_BMP085 bmp;
  
void setup() {
    //Wire.pins(sda,slc)
//  SWire.pins(4,5)
  //Wire.begin(4,5);
   #ifdef USBHID
    Serial.begin(9600);
   #else
    Serial.begin(31250);
   #endif

#ifdef GYRO
  mpu6050.begin(A2,A3,1);
  mpu6050.calcGyroOffsets(true);
#endif

  if (!bmp.begin(3,A2,A3)) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	//while (1) {}
  }
}

void PrintCount(){
#ifdef PRINTS
           count++;
         Serial.println(count);
         #endif
}
  
void loop() {
   hits = 9;
   
  samplebuffer=0;
  
    startMillis = millis(); // Start of sample window

  while (elapsedmilis < sampleWindow)
  {
    //if (digitalRead(OUT_PIN) < 1) { //microphone input
    //  samplebuffer++;
   // }
   
    samplebuffer += bmp.readPressure();
    elapsedmilis = millis() - startMillis;
  }

   //first drum loop
  if (samplebuffer > 0) {
    #ifdef PRINTS
    Serial.println(samplebuffer);
    #endif
    if (samplebuffer >= threshold1)
    {
      hits = 0;
      if (samplebuffer >= threshold2)
      {
        hits = 1;
        if (samplebuffer >= threshold3)
        {
          hits = 2;
        }
      }
    }

    Serial.println(hits);
         switch (hits) {
      case 2: {
          //noteOn(0x90, note, 127);
          #ifdef debug1
          Serial.println("hit2");
          PrintCount();
         #endif
         #ifdef PLAY
          //            delay(3003);
          note = 0x7;
          noteOn(0xB0,note, 0x127);
         // delay(10);
          //noteOn(0x90, note, 0x00);
          #endif
          break;
        }
      case 1: {
        #ifdef debug1
          Serial.println("hit1");
          #endif
          PrintCount();
         #ifdef PLAY
         note = 0x7;
            noteOn(0xB0, note, 0x85);
         //   delay(10);
         //   noteOn(0x90, note, 0x00);
           #endif 
          break;
        }
      case 0: {
        #ifdef debug1
            Serial.println("hit0");
            PrintCount();
          #endif
         #ifdef PLAY
          note = 0x7;
          noteOn(0xB0, note, 0x40);
         // delay(10);
         // noteOn(0x90, note, 0x00);
        #endif
        break;
        }  
    }
  }

#ifdef GYRO
  mpu6050.update();

//  if(millis() - timer > 1000){
    #ifdef PRINTS
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
 //   timer = millis();
    #endif
//  }
#endif

   // Serial.print("Temperature = ");
   // Serial.print(bmp.readTemperature());
   // Serial.println(" *C");
   
    //Serial.print("Pressure = ");
   // Serial.print(bmp.readPressure());
   // Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
   // Serial.print("Altitude = ");
   // Serial.print(bmp.readAltitude());
   // Serial.println(" meters");

  //  Serial.print("Pressure at sealevel (calculated) = ");
  //  Serial.print(bmp.readSealevelPressure());
  //  Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  //  Serial.print("Real altitude = ");
  //  Serial.print(bmp.readAltitude(104000)); //local is 1040 milibar x 100 = pascals//101500
 //   Serial.println(" meters");
   elapsedmilis=0;
      samplebuffer = 0;
      
   // Serial.println();
    delay(10);
}

 void noteOn(byte cmd, byte pitch, byte velocity) {
   /* First parameter is the event type (top 4 bits of the command byte).
      Second parameter is command byte combined with the channel.
      Third parameter is the first data byte
      Fourth parameter second data byte, if there is one:
  */
  #ifdef USBHID
    midiEventPacket_t midiMsg = {cmd >> 4, cmd, pitch, velocity};
    MidiUSB.sendMIDI(midiMsg);
   MidiUSB.flush();
   
   #ifdef debug
    //prints the values in the serial monitor so we can see what note we're playing
//    Serial.print("cmd: ");
//    Serial.print(cmd);
//    Serial.print(", data1: ");
//    Serial.print(data1);
//    Serial.print(", data2: ");
//    Serial.println(data2);
   #endif
   
  #else
  #ifdef PRINTS
    Serial.write( cmd );
    Serial.write( pitch );
    Serial.write( velocity );
    #endif
  #endif
}
