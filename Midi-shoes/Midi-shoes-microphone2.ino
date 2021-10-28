//credits for code
//https://github.com/olavxxx/Arduino-Sound-Sensor/blob/master/Soundsensor/Soundsensor.ino
//http://timewitharduino.blogspot.com/2014/01/isr-based-sketch-for-adafruit-coin.html


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMK:'.lNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMW0XMMMMMMMMMMMMMMMMN......c0MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMX'..lWMMMMMMMMMMMMMMd........'xNWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMl....,XMMMMMMMMMMMMMx............oXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMl .....XMMMMMMMMMMKc..........   ..0KNWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMM:  ....,WMMMMMWKo'.....................dNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMx....... .oxdl,.............................':OMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMM0.....'''.......................................;xxdKMMMMMMMMMMMMMMMMMMMM
//MMMMW, ...':clll;.....................................   ,kWMMMMMMMMMMMMMMMMMM
//MMMMo    ...',,.............................................cd0NMMMMMMMMMMMMMM
//MMMN.   ... .....................................................;ldOXWMMMMMMM
//MMWo   ................................................................':lxOKN
//MMc.   .......................................................................
//microphone..'.... ............................ ...............................
//N. ...'...................................    ................................microphone
//,  ..''''.....................................................................
//o......................................................................,,',cxX
//MO;....................       ......................................';lWWWWWWM
//
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
// place 2 microphones where directed on front and back of shoe



// get loudest toe when sorting the messages unless both are above stomp threshold

//uses blue microphone module from ebay.

 #ifndef __AVR__
 #endif
 
#define debug // not able to be used with tx line for older arduinos
//#define PLAY // disable this if debug is needed on older arduino
#define USBHID

#ifdef USBHID
    #include "MIDIUSB.h"
#endif

const int OUT_PIN = 3;
const int OUT_PIN1 = 0;
const int OUT_PIN2 = 1;
const int OUT_PIN3 = 1;

//for arduino nano
const int sampleWindow = 100; // Sample window width in mS (50 mS = 20Hz)
const int threshold1 = 20;    // 350 higher value for larger sample window
const int threshold2 = 90;
const int threshold4 = 140;
const int threshold3 = 200; //rename to 4 after

int samplebuffer = 0;

unsigned long startMillis;
long elapsedmilis = 0;

#ifdef calibrate
#include <EEPROM.h>
#endif

//#define calibrate
#ifdef calibrate
#else
#define lshoe
#define rshoe
#endif

void setup() {
  Serial.begin(9600);
}

void PrintCount() {
  count++;
  Serial.print("count");
  Serial.print(count);
}

void loop() {

  startMillis = millis(); // Start of sample window
  while (elapsedmilis < sampleWindow)
  {
    if (digitalRead(OUT_PIN) < 1) {
      samplebuffer++;
    }
        #ifdef DRUM2
    if (digitalRead(OUT_PIN1) < 1) {
      samplebuffer1++;
    }
    #endif
    
    elapsedmilis = millis() - startMillis;
  }

#ifdef calibrate
  if (samplebuffer >= threshold1)
  {
    avgnum += samplebuffer;
    countavg++;
    Serial.println(avgnum / countavg);
    Serial.println(samplebuffer);
    PrintCount();
  }
#endif


#ifdef rshoe
//first drum loop
  if (samplebuffer > 0) {
    //Serial.println(sampleBufferValue);

    if (samplebuffer >= threshold1)
    {
      hits = 0;
      if (samplebuffer >= threshold2)
      {
        hits = 1;
        if (samplebuffer >= threshold3)
        {
          hits = 2;
        }
      }
    }
    
    switch (hits) {
      case 2: {
          //noteOn(0x90, note, 127);
          #ifdef debug
          Serial.println("hit2");
          PrintCount();
         #endif
         #ifdef PLAY
          //            delay(3003);
          note = 0x4E;
          noteOn(0x90, note, 0x45);
          delay(10);
          //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
          noteOn(0x90, note, 0x00);
          #endif
          break;
        }
      case 1: {
        #ifdef debug
          Serial.println("hit1");
          #endif
          PrintCount();
         #ifdef PLAY
            //  for (int note = 0x1E; note < 0x5A; note ++) {
            note = 0x5E;
            noteOn(0x90, note, 0x45);
            delay(10);
            //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
            noteOn(0x90, note, 0x00);
           #endif 
          break;
        }
      case 0: {
        #ifdef debug
            Serial.println("hit0");
            PrintCount();
          #endif
         #ifdef PLAY
          noteOn(0x90, note, 0x45);
          delay(10);
          //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
          noteOn(0x90, note, 0x00);
      //    delay(10);
        #endif
          break;
        }
    }
  }

#ifdef DRUM2
  //second drum loop
  if (samplebuffer1 > 0) {
    //Serial.println(sampleBufferValue);

    if (samplebuffer1 >= threshold1)
    {
      hits1 = 0;
      if (samplebuffer1 >= threshold2)
      {
        hits1 = 1;
        if (samplebuffer1 >= threshold3)
        {
          hits1 = 2;
        }
      }
    }
    
    switch (hits1) {
      case 2: {
          //noteOn(0x90, note, 127);
          #ifdef debug
          Serial.println("hit2");
                    PrintCount();
          #endif
         #ifdef PLAY
          note = 0x4E;
          noteOn(0x90, note, 0x45);
          delay(10);
          noteOn(0x90, note, 0x00);
          #endif
          break;
        }
      case 1: {
        #ifdef debug
          Serial.println("hit1");
                    PrintCount();
          #endif
         #ifdef PLAY
            note = 0x5E;
            noteOn(0x90, note, 0x45);
            delay(10);
            noteOn(0x90, note, 0x00);
           #endif 
          break;
        }
      case 0: {
        #ifdef debug
            Serial.println("hit0");
                      PrintCount();
          #endif
         #ifdef PLAY
          noteOn(0x90, note, 0x45);
          delay(10);
          noteOn(0x90, note, 0x00);
        #endif
          break;
        }
         count++;
         Serial.println(count);
    }
  }
#endif // rshoe


#ifdef lshoe
    //first drum loop
  if (samplebuffer2 > 0) {
    //Serial.println(sampleBufferValue);

    if (samplebuffer2 >= threshold1)
    {
      hits = 0;
      if (samplebuffer2 >= threshold2)
      {
        hits = 1;
        if (samplebuffer2 >= threshold3)
        {
          hits = 2;
        }
      }
    }
    
    switch (hits) {
      case 2: {
          //noteOn(0x90, note, 127);
          #ifdef debug
          Serial.println("hit2");
          PrintCount();
         #endif
         #ifdef PLAY
          //            delay(3003);
          note = 0x4E;
          noteOn(0x90, note, 0x45);
          delay(10);
          //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
          noteOn(0x90, note, 0x00);
          #endif
          break;
        }
      case 1: {
        #ifdef debug
          Serial.println("hit1");
          #endif
          PrintCount();
         #ifdef PLAY
            //  for (int note = 0x1E; note < 0x5A; note ++) {
            note = 0x5E;
            noteOn(0x90, note, 0x45);
            delay(10);
            //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
            noteOn(0x90, note, 0x00);
           #endif 
          break;
        }
      case 0: {
        #ifdef debug
            Serial.println("hit0");
            PrintCount();
          #endif
         #ifdef PLAY
          noteOn(0x90, note, 0x45);
          delay(10);
          //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
          noteOn(0x90, note, 0x00);
      //    delay(10);
        #endif
          break;
        }
    }
  }


  //second drum loop
  if (samplebuffer3 > 0) {
    //Serial.println(sampleBufferValue);

    if (samplebuffer3 >= threshold1)
    {
      hits1 = 0;
      if (samplebuffer3 >= threshold2)
      {
        hits1 = 1;
        if (samplebuffer3 >= threshold3)
        {
          hits1 = 2;
        }
      }
    }
    
    switch (hits1) {
      case 2: {
          //noteOn(0x90, note, 127);
          #ifdef debug
          Serial.println("hit2");
                    PrintCount();
          #endif
         #ifdef PLAY
          note = 0x4E;
          noteOn(0x90, note, 0x45);
          delay(10);
          noteOn(0x90, note, 0x00);
          #endif
          break;
        }
      case 1: {
        #ifdef debug
          Serial.println("hit1");
                    PrintCount();
          #endif
         #ifdef PLAY
            note = 0x5E;
            noteOn(0x90, note, 0x45);
            delay(10);
            noteOn(0x90, note, 0x00);
           #endif 
          break;
        }
      case 0: {
        #ifdef debug
            Serial.println("hit0");
                      PrintCount();
          #endif
         #ifdef PLAY
          noteOn(0x90, note, 0x45);
          delay(10);
          noteOn(0x90, note, 0x00);
        #endif
          break;
        }
         count++;
         Serial.println(count);
    }
  }
#endif // lshoe


  /***
    Need to divide by 4 because analog inputs range from
    0 to 1023 and each byte of the EEPROM can only hold a
    value from 0 to 255.
  ***/
 // int val = analogRead(0) / 4;
  /***
    Write the value to the appropriate byte of the EEPROM.
    these values will remain there when the board is
    turned off.
  ***/
 // EEPROM.write(addr, val);
 

 samplebuffer = 0;
  samplebuffer1 = 0;
  samplebuffer2 = 0;
  samplebuffer3 = 0;
  samplebuffer4 = 0;
  samplebuffer5 = 0;


  elapsedmilis = 0;

}

 void noteOn(byte cmd, byte pitch, byte velocity) {
   /* First parameter is the event type (top 4 bits of the command byte).
      Second parameter is command byte combined with the channel.
      Third parameter is the first data byte
      Fourth parameter second data byte, if there is one:
  */
  #ifdef USBHID
    midiEventPacket_t midiMsg = {cmd >> 4, cmd, pitch, velocity};
    MidiUSB.sendMIDI(midiMsg);
   MidiUSB.flush();
   
   #ifdef debug
    //prints the values in the serial monitor so we can see what note we're playing
//    Serial.print("cmd: ");
//    Serial.print(cmd);
//    Serial.print(", data1: ");
//    Serial.print(data1);
//    Serial.print(", data2: ");
//    Serial.println(data2);
   #endif
   
  #else
    Serial.write( cmd );
    Serial.write( pitch );
    Serial.write( velocity );
  #endif
}

//
//#ifdef USBHIDs
//
//void noteOn(byte channel, byte pitch, byte velocity) {
//  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
//  MidiUSB.sendMIDI(noteOn);
//      MidiUSB.flush();
//}
//
//void noteOff(byte channel, byte pitch, byte velocity) {
//  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
//  MidiUSB.sendMIDI(noteOff);
//      MidiUSB.flush();
//}
//
//// First parameter is the event type (0x0B = control change).
//// Second parameter is the event type, combined with the channel.
//// Third parameter is the control number number (0-119).
//// Fourth parameter is the control value (0-127).
//
//void controlChange(byte channel, byte control, byte value) {
//  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
//  MidiUSB.sendMIDI(event);
//}
//#endif
