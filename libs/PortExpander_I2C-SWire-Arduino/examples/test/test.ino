#include <PortExpander_I2C-swire.h>

PortExpander_I2C pe(0x20,6,7);

void setup() {  
  pe.init();
  Serial.begin(115200);
  for( int i = 0; i < 8; i++ ){
    pe.pinMode(i,INPUT);
  }
  pe.pinMode(0,OUTPUT);

    pe.digitalWrite(0, LOW);
}

void loop() {
  for( int i = 0; i < 8; i++ ){
    i=1;
    if( pe.digitalRead(i) == 0 ){
      Serial.print("Pin " );
      Serial.print(i);
      Serial.println(" is low.");
    }
    delay(5);
  }
}
