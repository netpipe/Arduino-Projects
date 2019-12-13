#include "Arduino.h"
//#undef __AVR
//#define __AVR
#include "PCF8574-swire.h"

// Set i2c address
PCF8574 pcf8574(0x20 , 6, 7 );

unsigned long timeElapsed;
void setup()
{
	Serial.begin(115200);

	pcf8574.pinMode(P0, OUTPUT); 
	pcf8574.pinMode(P1, INPUT);

	pcf8574.begin();
}

void loop()
{
      pcf8574.digitalWrite(P0, HIGH);
	uint8_t val = pcf8574.digitalRead(P1);
	if (val==HIGH) Serial.println("KEY PRESSED");
	delay(50);
  
Serial.println("loop");
  delay(100);
  pcf8574.digitalWrite(P0, LOW);
}
