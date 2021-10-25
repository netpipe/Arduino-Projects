/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Midi
*/
const int ledPin = 13;   
const int knockSensor0 = A0;
const int knockSensor1 = A1;
const int threshold0 = 1000;
const int threshold1 = 500;
const int knockSensor2 = A2;
const int knockSensor3 = A3;
const int threshold2 = 1000;
const int threshold3 = 500;

int sensorReading0 = 0;  
int sensorReading1 = 1;
int sensorReading2 = 2;  
int sensorReading3 = 3;// variable to store the value read from the sensor pin
int ledState = LOW; 


void setup() {
  // Set MIDI baud rate:
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);
}

void loop() {

    sensorReading0 = analogRead(knockSensor0);
    sensorReading1 = analogRead(knockSensor1);
    sensorReading2 = analogRead(knockSensor2);
    sensorReading3 = analogRead(knockSensor3);
  // if the sensor reading is greater than the threshold:
  
  if (sensorReading0 >= threshold0) 
  {
    

    // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  //  for (int note = 0x1E; note < 0x5A; note ++) {
      //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
     // noteOn(0x90, note, 0x45);
      delay(80);
      //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    //  noteOn(0x90, note, 0x00);
      Serial.println("Knock0!");
  //  }
  }
    if (sensorReading1 >= threshold1) 
  {
          delay(80);
            Serial.println("Knock1!");
  }
      if (sensorReading2 >= threshold2) 
  {
          delay(80);
            Serial.println("Knock2!");
  }
      if (sensorReading3 >= threshold3) 
  {
          delay(80);
            Serial.println("Knock3!");
  }
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
