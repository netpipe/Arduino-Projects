#include <PortExpander_I2C-swire.h>
#include <Adafruit_SSD1306-swire.h>
#include <Adafruit_GFX.h>
#include "HX711.h"

HX711 scale;
// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


//PortExpander_I2C pe(0x20,6,7);

//int val1;
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
  Serial.begin(9600);
    Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");
  scale.begin(A1, A0);


  Serial.print("Raw ave(20): \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  // Scale factor:
  // 1Kg cell: 2020 for reading in gms
  // 50kg cells: 19150 for reading in kg
  scale.set_scale(2020.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("\nAfter setting up the scale:");

  Serial.print("Raw: \t\t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("Raw ave(20): \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("Raw ave(5) - tare: \t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("Calibrated ave(5): \t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("\nReadings:");

///  pe.init();



  
 // for( int i = 0; i < 8; i++ ){
 //   pe.pinMode(i,INPUT);
 // }
 // pe.pinMode(0,OUTPUT);

//    pe.pinMode (encoder0PinA, INPUT);
//    pe.pinMode (encoder0PinB, INPUT);
//    //pinMode (9, INPUT);
//       // digitalWrite (9, HIGH);
//               //    pe.pinMode (4, INPUT);
//              //     pe.pinMode (4, INPUT);
//    pe.digitalWrite(0, LOW);
//    pe.digitalWrite(3, HIGH);
//        
   // pe.pinMode (4, INPUT);
   // pe.pinMode (5, OUTPUT);
   // pe.pinMode (6, OUTPUT);

    //pe.digitalWrite(5, LOW);
   // pe.digitalWrite(6, HIGH);


//if pe

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR,1,4,5);

  
}
  int i=0;

   float val2;
   bool bcalibrate=0;
   float tear;
   float correction=100; // set to check if its been changed and to trigger the calibrated6
  // float calammount;

  // float readLoadCell(){};
  // float calibrated(){};
   
void loop() {


 
  if ( i == 0 ){ // update display initial logo
      tear = readLoadCell();
    display.clearDisplay();
   // display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,30); //x y
    display.print("Teared. Get ready to place weight!");
    display.display();
     
           delay(545);
    i=2;
   }
 

    display.clearDisplay();
    //display.display();

        
//add tear function.
    display.setCursor(10,10); //x y
    display.print("teared");
  //  display.display();


  if (bcalibrate==0){
    correction = calibrated();
    display.setCursor(50,10); //x y
    display.print(correction);
    //delay(55);
  }else{
    display.setCursor(50,10); //x y
    display.print(correction);
   // delay(55);
       }

   // display.clearDisplay();
  //  display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(47,30); //x y
       display.print("corrected weight: ");
    //   display.print("\n");
    val2 = readLoadCell();
    
    if ((val2-correction)<=-1){  // get the scale back to 0 without weight.
  //  display.print(val2-correction);
      //display.print(correction+val2);
      display.print(val2-tear);
    }else{
      display.print(val2-correction);
        
      }
    
    display.display();
  //  delay(145);


    
   
//if (digitalRead(9) == HIGH) {
//                  Serial.print ("TESTING PROBE \n");
//        Serial.print (digitalRead(9));
//}

   //if(count < countsperrev )
 //   clockwise();
 // else if (count == countsperrev * 2)
 //   count = 0;
 // else
 //   anticlockwise();
//  count++;
 // motorSpeed--;       
  
   //   n = pe.digitalRead(encoder0PinA);

//  if ((encoder0PinALast == HIGH) && (n == LOW)) {
//    //if (pe.digitalRead(encoder0PinB) == HIGH) {
//      encoder0Pos--;
//        Serial.print ("--");
//      //  Serial.print (pe.digitalRead(encoder0PinB));
//        Serial.print ("\n");
//    } else {
//      encoder0Pos++;
//       // Serial.print (pe.digitalRead(encoder0PinB      ));
//            Serial.print ("++");
//    Serial.print ("\n");
//    }
//      Serial.print (encoder0Pos);
//       Serial.print ("/");
       
   //     if (pe.digitalRead(4) == HIGH) {
   //       Serial.print ("optical endstop triggered");
   //     }
          
 //   delay(5);

///    encoder0PinALast = n;


}

float calibrated(){ //return correction value for weight per gram
//correction factor 100grams reads 112
  //calibrate with 100 gram weight
  //if (bcalibrate == 0){
       float weight=100;
    //tear = readLoadCell(); //no need to reread

        display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,0); //x y
           // display.setCursor(25,30); //x y
       display.print("Calibrating... Place Weight on scale");
    display.display();
      delay(1455);
    

       
      val2 = readLoadCell();
     // calibration weight ammount;
   
    if (val2 >= weight){
       correction= val2 - weight;
       if (correction <=50 ){
           bcalibrate=1;
        return (correction);
       }
      }else if(val2 <= weight){      
       correction= weight - val2 ;
             if (correction <=50 ){
           bcalibrate=1;
        return (correction);
             }
      }
//  }
}

float readLoadCell(){

  
  int T;
  double val;
  double sum;
  double sumsq;
  double mean;
  float stddev;
  
  int nt = 20;
  int t = millis();
  int it = sum = sumsq = 0;
  while (it<nt) {
    val = ((scale.read() - scale.get_offset()) / scale.get_scale()  );
    sum += val ;
    sumsq += val * val;
    it++;
  }
  t = millis() - t;
  mean = sum / nt;
  stddev = sqrt(sumsq / nt - mean * mean);
  Serial.print("Mean, Std Dev of "); Serial.print(i); Serial.print(" readings:\t");
  Serial.print(sum / nt, 3); Serial.print("\t"); Serial.print(stddev, 3);
  // Note: 2 sigma is 95% confidence, 3 sigma is 99.7%
  Serial.print("\nTime taken:\t"); Serial.print(float(t)/1000, 3); Serial.println("Secs\n");


return (sum / nt * 2 * 1.10);
}

//
//// stepper functions
//void anticlockwise()
//{
//  for(int i = 0; i < 8; i++)
//  {
//    setOutput(i);
//    delayMicroseconds(motorSpeed);
//  }
//}
//
//void clockwise()
//{
//  for(int i = 7; i >= 0; i--)
//  {
//    setOutput(i);
//    delayMicroseconds(motorSpeed);
//  }
//}

//void setOutput(int out)
//{
//  pe.digitalWrite(motorPin1, bitRead(lookup[out], 0));
//  pe.digitalWrite(motorPin2, bitRead(lookup[out], 1));
//  pe.digitalWrite(motorPin3, bitRead(lookup[out], 2));
//  pe.digitalWrite(motorPin4, bitRead(lookup[out], 3));
//}
