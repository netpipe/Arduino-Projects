/*
   Bas on Tech
   This course is part of the courses on https://arduino-tutorials.net
   (c) Copyright 2020 - Bas van Dijk / Bas on Tech
   This code and course is copyrighted. It is not allowed to use these courses commercially
   without explicit written approval
   YouTube:    https://www.youtube.com/c/BasOnTech
   Facebook:   https://www.facebook.com/BasOnTechChannel
   Instagram:  https://www.instagram.com/BasOnTech
   Twitter:    https://twitter.com/BasOnTech
   
*/

//uses blue microphone module from ebay.

const int OUT_PIN = 8;
const int SAMPLE_TIME = 100;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

const int threshold1 = 50;
const int threshold2 = 500;
const int threshold3 = 1000;

int sampleBufferValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(OUT_PIN) == LOW) {
    sampleBufferValue++;
  }

  if (millisElapsed > SAMPLE_TIME) {
    if (sampleBufferValue > 0){
    Serial.println(sampleBufferValue);
    
    if (sampleBufferValue >= threshold1) 
  {
      //    delay(80);
            Serial.println("Knock1!");
  }
      if (sampleBufferValue >= threshold2) 
  {
       //   delay(80);
            Serial.println("Knock2!");
  }
      if (sampleBufferValue >= threshold3) 
  {
      //    delay(80);
            Serial.println("Knock3!");
  }
  
      }
    sampleBufferValue = 0;
    millisLast = millisCurrent;

  }

  
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
