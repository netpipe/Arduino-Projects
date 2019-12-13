#include <PortExpander_I2C-swire.h>

PortExpander_I2C pe(0x20,6,7);

int val;
int encoder0PinA = 1;
int encoder0PinB = 2;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;



void setup() {  
  pe.init();
  Serial.begin(115200);
 // for( int i = 0; i < 8; i++ ){
 //   pe.pinMode(i,INPUT);
 // }
 // pe.pinMode(0,OUTPUT);

    pe.pinMode (encoder0PinA, INPUT);
    pe.pinMode (encoder0PinB, INPUT);

    pe.digitalWrite(0, LOW);
}

void loop() {

      n = pe.digitalRead(encoder0PinA);

  if ((encoder0PinALast == HIGH) && (n == LOW)) {
    if (pe.digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos--;
                  Serial.print ("--");
        Serial.print (pe.digitalRead(encoder0PinB));
    Serial.print ("\n");
    } else {
      encoder0Pos++;
        Serial.print (pe.digitalRead(encoder0PinB      ));
            Serial.print ("++");
    Serial.print ("\n");
    }
    Serial.print (encoder0Pos);
    Serial.print ("/");
    
    delay(5);
  }
    encoder0PinALast = n;
}
