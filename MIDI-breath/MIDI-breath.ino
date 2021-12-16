//#define USBHID
#ifdef USBHID
    #include "MIDIUSB.h"
#endif

#define PLAY

int hits;
unsigned long startMillis;
long elapsedmilis = 0;

const int OUT_PIN = 3;

#ifdef memory
#include <EEPROM.h>
int addr = 0;
#endif

byte note = 0;

#define MIDI_ON 144
#define MIDI_OFF 128

int samplebuffer = 0;

const int sampleWindow = 28; // Sample window width in mS (50 mS = 20Hz)
const int threshold1 = 26400;    // 350 higher value for larger sample window
const int threshold2 = 27000;
//const int threshold4 = 140; 
const int threshold3 = 28000; //rename to 4 after
int count = 0;

#include <SWire.h>
#include <Adafruit_BMP085-swire.h>

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;
  
void setup() {
    //Wire.pins(sda,slc)
//  SWire.pins(4,5)
  //Wire.begin(4,5);
   #ifdef USBHID
    Serial.begin(9600);
              #else
   // Serial.begin(31250);
    #endif
     Serial.begin(9600);

  if (!bmp.begin(3,A4,A5)) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	//while (1) {}
  }
}

void PrintCount(){

           count++;
         Serial.println(count);
         
}
  
void loop() {
   hits = 9;
   
  samplebuffer=0;
  
    startMillis = millis(); // Start of sample window

  while (elapsedmilis < sampleWindow)
  {
    //if (digitalRead(OUT_PIN) < 1) {
    //  samplebuffer++;
   // }
   
    samplebuffer += bmp.readPressure();
    elapsedmilis = millis() - startMillis;
  }

   //first drum loop
  if (samplebuffer > 0) {
    Serial.println(samplebuffer);

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
          #ifdef debug
          Serial.println("hit2");
          PrintCount();
         #endif
         #ifdef PLAY
          //            delay(3003);
          note = 0x4E;
          noteOn(0x9A, 0x02, 0x45);
          #endif
          
        }break;
      case 1: {
        #ifdef debug
          Serial.println("hit1");
          #endif
          PrintCount();
         #ifdef PLAY
            noteOn(0x9A, 0x01, 0x45);
           #endif 
          
        }break;
      case 0: {
        #ifdef debug
            Serial.println("hit0");
            PrintCount();
          #endif
         #ifdef PLAY
          noteOn(0x9A, 0x00, 0x45);
        #endif
       
        }   break;
    }
  }

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
    Serial.write( cmd );
    Serial.write( pitch );
    Serial.write( velocity );
  #endif
}
