// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(2);

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo
int pos = 0;  // variable to store the servo position


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(200);
 
  motor.run(RELEASE);

  myservo.attach(10);   
  //myservo.attach(9); 
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");
  
  motor.run(FORWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);  
 //   delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
  //  delay(10);
 }
  
  Serial.print("tock");

  motor.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);  
  //  delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
  //  delay(10);
 }
  

  Serial.print("tech");
  motor.run(RELEASE);


    // sweeps from 0 degrees to 180 degrees
  for(pos = 0; pos <= 180; pos += 1) 
  {
    myservo.write(pos);
    delay(15);
  }
  // sweeps from 180 degrees to 0 degrees
  for(pos = 180; pos>=0; pos-=1)
  {
    myservo.write(pos);
    delay(15);
  }

  
  delay(10);
}
