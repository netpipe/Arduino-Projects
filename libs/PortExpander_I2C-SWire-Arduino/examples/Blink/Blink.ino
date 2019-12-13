#include <PortExpander_I2C.h>

PortExpander_I2C pe(0x20);
int ledPin = 7; // This is the eighth expansion port

void setup() {  
  pe.init();
}

void loop() {
  pe.digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  pe.digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                     // wait for a second
}
