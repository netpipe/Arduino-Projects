// This Arduino example demonstrates bidirectional operation of a
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.
////////////////////////////////////////////////

// this arrangement is better than stepper.h for torque
// still WIP for some reason the motor is only using 2 of the pins
#ifdef EXPANDER
#include <PortExpander_I2C-swire.h>
PortExpander_I2C pe(0x38,A4,A5);
#endif

int mpos[]={0,0,0,0}; //4 motors 1 to 8 position lookup table has continous mode modulus too


//declare variables for the motor pins 
int motorPin1 = 0;    
int motorPin2 = 0;    
int motorPin3 = 0;   
int motorPin4 = 0;   
//leave as 0

static char motor1Pins[]= {A0,A1,A2,A3};
//static int motor1Pins[]= {0,1,2,3};
static int motor2Pins[]= {4,5,6,7};
static int motor3Pins[]= {8,9,10,11};
static int motor4Pins[]= {12,13,14,15};


int motorSpeed = 1200;  //variable to set stepper speed
                        // Experiment with this; too small will not work.
int count = 0;          // count of steps made
int countsperrev = 560; // number of steps per revolution for this motor

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};



void setup() 
  {
  //declare the motor pins as outputs
  for (int i=0; i < 1; i++){
    setmotor(i);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
      digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  }
#ifdef EXPANDER
  pe.pinMode(motorPin1, OUTPUT);
  pe.pinMode(motorPin2, OUTPUT);
  pe.pinMode(motorPin3, OUTPUT);
  pe.pinMode(motorPin4, OUTPUT);
  pe.digitalWrite(motorPin1, LOW);
  pe.digitalWrite(motorPin2, LOW);
  pe.digitalWrite(motorPin3, LOW);
  pe.digitalWrite(motorPin4, LOW);
#endif
                  
  Serial.begin(9600);
  }

void loop()
  {
    for (int i=0; i < countsperrev;i++){
      step(1,0); // direction and motor  -- not moving in negative direction yet
      //anticlockwise();
    }
  }

  void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}


void step(char dir,int motor) // direction is set with 1/-1
{
  mpos[motor] = (mpos[motor] + dir) % 8;
  //  Serial.println("motor position");
  //Serial.println(mpos[motor]);
  
  setmotor(motor);

}



void setmotor(int motor){
  
  switch(motor){
  case 0:
    motorPin1 = motor1Pins[0];
    motorPin2 = motor1Pins[1];   
    motorPin3 = motor1Pins[2];   
    motorPin4 = motor1Pins[3];
    setOutput(mpos[motor]);
      delayMicroseconds(motorSpeed);
    break;  
  case 1:
    motorPin1 = motor2Pins[0];
    motorPin2 = motor2Pins[1];   
    motorPin3 = motor2Pins[2];   
    motorPin4 = motor2Pins[3];
    setOutput(mpos[motor]);
      delayMicroseconds(motorSpeed);
    break;  
  case 2:
    motorPin1 = motor3Pins[0];
    motorPin2 = motor3Pins[1];   
    motorPin3 = motor3Pins[2];   
    motorPin4 = motor3Pins[3];
    setOutput(mpos[motor]);
      delayMicroseconds(motorSpeed);
    break;  
  case 3: // i2c expander
    motorPin1 = motor4Pins[0];
    motorPin2 = motor4Pins[1];   
    motorPin3 = motor4Pins[2];   
    motorPin4 = motor4Pins[3];
    setOutputpe(mpos[motor]);
      delayMicroseconds(motorSpeed);
    break;  
  }
  
}

void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}

void setOutputpe(int out)
{
  #ifdef EXPANDER
    pe.digitalWrite(motorPin1, bitRead(lookup[out], 0));
    pe.digitalWrite(motorPin2, bitRead(lookup[out], 1));
    pe.digitalWrite(motorPin3, bitRead(lookup[out], 2));
    pe.digitalWrite(motorPin4, bitRead(lookup[out], 3));
  #endif
}
