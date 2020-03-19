/* The code was made by Tamás Imets for an Arduino UNO project
   This code controls the BB-8 Droid from the Star Wars: The Force Awakens,
   and works with Bluetooth RC Car application, using a HC-06 seriaé bluetooth module
   See more details at instructables.com/member/Imetomi
   Friday,  December 25, 2015
 */
//https://www.instructables.com/id/DIY-Bluetooth-Phone-Controlled-BB-8-Droid-With-Ard/

#include <Servo.h>
#include <SoftwareSerial.h>
#include <AFMotor.h>
int command = 0;  //incoming serial data


AF_DCMotor motor1(1, MOTOR12_64KHZ); //initialize motor1 that is connected to the M1 port, this motor moves forward and backward
AF_DCMotor motor2(2, MOTOR12_64KHZ); //motor2 is connected to M2 and this turns BB-8 left and right

Servo head;
void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps - this is the speed the serial interface will work all
  head.attach(9); //attach servo to pin D9 or to servo2 on motor shield
  motor1.setSpeed(255); //set default speed
  motor2.setSpeed(255); //set default speed
  pinMode(13, OUTPUT); //connect here the blue LED
}

void loop() {
  if (Serial.available() > 0) { //if the Arduino detects incoming data
    // read the incoming byte:
    command = Serial.read();
  }
  switch (command) //set different cases of the "command" variable
  {
    case 'S': {
        motor1.run(RELEASE); // stopped
        motor2.run(RELEASE); // stopped
        command = '*';
      } break;

    case 'F': { //go forward
        motor2.run(RELEASE);
        motor1.run(FORWARD);
      } break;

    case 'B': { //go backward
        motor2.run(RELEASE);
        motor1.run(BACKWARD);
      } break;

    case 'R': { //spin right
        motor1.run(RELEASE);
        motor2.run(FORWARD);
      } break;

    case 'L': { //spin left
        motor1.run(RELEASE);
        motor2.run(BACKWARD);
      } break;

    case 'G': { //forward left
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
      } break;

    case 'I': { //forward right
        motor1.run(FORWARD);
        motor2.run(FORWARD);
      } break;

    case 'H': { //backward left
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
      } break;

    case 'J': { //backward right
        motor1.run(BACKWARD);
        motor2.run(FORWARD);
      } break;

    case 'W': {
        digitalWrite(13, HIGH); //lights on
      } break;

    case 'w': {
        digitalWrite(13, LOW); //lights off
      } break;

    case 'U': {
        motor1.setSpeed(128); //set lower speed
      } break;

    case 'u': {
        motor1.setSpeed(255); //set max speed
      } break;

    case '0': {
        head.write(95); //basic servo state
      } break;

    case '1': {
        head.write(50); //move servo
      } break;

    case '2': {
        head.write(60); //move servo
      } break;


    case '3': {
        head.write(70); //move servo
      } break;


    case '4': {
        head.write(80); //move servo
      } break;


    case '5': {
        head.write(90); //move servo
      } break;


    case '6': {
        head.write(95); //move servo
      } break;


    case '7': {
        head.write(110); //move servo
      } break;


    case '8': {
        head.write(120); //move servo
      } break;

    case '9': {
        head.write(130); //move servo
      } break;

    case 'q': {
        head.write(135); //move servo
      } break;
   //you can add more extra feautres by writing a case command (example: different lights, sound, etc...)
  }
}
