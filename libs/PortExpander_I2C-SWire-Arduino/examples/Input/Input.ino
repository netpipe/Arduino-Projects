#include <PortExpander_I2C.h>

PortExpander_I2C pe(0x20);

void setup() {  
  pe.init();
  Serial.begin(9600);
  for( int i = 0; i < 8; i++ ){
    pe.pinMode(i,INPUT);
  }
}

void loop() {
  for( int i = 0; i < 8; i++ ){
    if( pe.digitalRead(i) == 0 ){
      Serial.print("Pin " );
      Serial.print(i);
      Serial.println(" is low.");
    }
  }
}
