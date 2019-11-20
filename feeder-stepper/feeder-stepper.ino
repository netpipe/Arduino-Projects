#include <PortExpander_I2C-swire.h>
#include <Adafruit_SSD1306-swire.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


PortExpander_I2C pe(0x20,6,7);

int val;
int encoder0PinA = 1;
int encoder0PinB = 2;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

// stepper motor
int motorPin1 = 4;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 5;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 6;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 7;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)

int motorSpeed = 710;  //variable to set stepper speed
                  // 700 and 710 start on their own anymore and you need ramping
                  //1500 was pretty good
                  
int count = 0;          // count of steps made
int countsperrev = 200; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};




void setup() {  
  pe.init();
  Serial.begin(115200);
 // for( int i = 0; i < 8; i++ ){
 //   pe.pinMode(i,INPUT);
 // }
 // pe.pinMode(0,OUTPUT);

    pe.pinMode (encoder0PinA, INPUT);
    pe.pinMode (encoder0PinB, INPUT);
    //pinMode (9, INPUT);
       // digitalWrite (9, HIGH);
               //    pe.pinMode (4, INPUT);
              //     pe.pinMode (4, INPUT);
    pe.digitalWrite(0, LOW);
    pe.digitalWrite(3, HIGH);
        
   // pe.pinMode (4, INPUT);
   // pe.pinMode (5, OUTPUT);
   // pe.pinMode (6, OUTPUT);

    //pe.digitalWrite(5, LOW);
   // pe.digitalWrite(6, HIGH);

  pe.pinMode(motorPin1, OUTPUT);
  pe.pinMode(motorPin2, OUTPUT);
  pe.pinMode(motorPin3, OUTPUT);
  pe.pinMode(motorPin4, OUTPUT);
      pe.digitalWrite(motorPin1, LOW);
          pe.digitalWrite(motorPin2, LOW);
              pe.digitalWrite(motorPin3, LOW);
                  pe.digitalWrite(motorPin4, LOW);


  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR,1,6,7);
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // update display with all of the above graphics
  display.display();

  
}
  int i=0;
  
void loop() {

  if ( i == 0 ){ // update display
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,30); //x y
    display.print("Hello, world!");
    display.setCursor(0,30);
    display.print("Hello, world2!");
    display.display();
    i=10;
   }
   
//if (digitalRead(9) == HIGH) {
//                  Serial.print ("TESTING PROBE \n");
//        Serial.print (digitalRead(9));
//}

   //if(count < countsperrev )
 //   clockwise();
 // else if (count == countsperrev * 2)
 //   count = 0;
 // else
    anticlockwise();
//  count++;
 // motorSpeed--;       
  
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
       
        if (pe.digitalRead(4) == HIGH) {
          Serial.print ("optical endstop triggered");
        }
          
    delay(15);
  }
    encoder0PinALast = n;
}



// stepper functions
void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out)
{
  pe.digitalWrite(motorPin1, bitRead(lookup[out], 0));
  pe.digitalWrite(motorPin2, bitRead(lookup[out], 1));
  pe.digitalWrite(motorPin3, bitRead(lookup[out], 2));
  pe.digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
