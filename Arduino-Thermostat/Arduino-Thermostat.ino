#include <PortExpander_I2C-swire.h>
#include <Adafruit_SSD1306-swire.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define BMP085
#ifdef BMP085
  #include <Adafruit_BMP085-swire.h> //might replace with bmp280 for temp and humidity in one
  #include <dht.h>
  Adafruit_BMP085 bmp;
  dht DHT;
  #define DHT11_PIN 7
#endif

// combine arduino with mercury switch incase of overheat failsafe while debugging
// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

PortExpander_I2C pe(0x20,4,5);
int ledPin = 7; // This is the eighth expansion port



#include <EEPROM.h>

struct TimeVar {
  byte hour;
  byte minute;
  byte second;
  bool operator == (const TimeVar& t)
  {
    return (hour == t.hour && minute == t.minute && second == t.second);
  }
  bool operator != (const TimeVar& t)
  {
    return (hour != t.hour || minute != t.minute || second != t.second);
  }
};

TimeVar remainingTime;
const TimeVar defaultTime = {0, 10, 30};  // program default time is 00:10:30 , zero hours, ten minutes and thirty seconds
unsigned long startTime = 0;
bool updated = false;


void setup() {  
  pe.init();
  Serial.begin(9600);

  for( int i = 0; i < 8; i++ ){
    pe.pinMode(i,INPUT);
    pe.digitalWrite(i, HIGH);
  }
  pe.pinMode (0, OUTPUT);    
  pe.pinMode (1, OUTPUT);
  pe.pinMode (2, INPUT);
  pe.pinMode (3, INPUT);
  pe.pinMode (5, INPUT);
  pe.pinMode (6, INPUT);
  pe.pinMode (7, INPUT);
 
  
  pe.digitalWrite(0, HIGH);
  pe.digitalWrite(1, LOW); 
  pe.digitalWrite(2, LOW); 
  pe.digitalWrite(3, HIGH); 
  pe.digitalWrite(4, HIGH); 
  pe.digitalWrite(5, HIGH);
  pe.digitalWrite(6, HIGH); 
  pe.digitalWrite(7, LOW);

  
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR,1,4,5);
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);
    display.setCursor(27,30); //x y
    display.print("Thermostat!");
 
  display.display();

//BMP085_ULTRALOWPOWER
//BMP085_STANDARD
//BMP085_HIGHRES
    if (!bmp.begin(BMP085_STANDARD,4,5)) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

}



  int i=0;
  int count=0;
int countit=0;
int activated=1;
bool pin3,pin4,pin5,pin6;
int temperature;


void loop() {

  
if ( count > 180 ){
  //  if ( i == 0 ){ // update display
    display.clearDisplay();
    display.display();
    display.setTextSize(0.5);
    display.setTextColor(WHITE);
  //  display.setCursor(27,30); //x y
  //  display.print("Hello, world!");
  //  display.setCursor(0,50);
 //   display.print("Hello, world2!");
  
  //  i=10;
  // }
   
 // pe.digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
 // delay(1000);                     // wait for a second
 // pe.digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
//  pe.digitalWrite(0, HIGH); 
 //  pe.digitalWrite(0, HIGH);  
  
      // if (pe.digitalRead(2) == HIGH) {
     //     Serial.print ("optical endstop triggered");
     //   }
// if (pe.digitalRead(3) !=0){
 
// }
 //}
// loop through pages of information
#ifdef BMP085
    display.setCursor(0,10);
    display.print("Temperature = ");
    display.print(bmp.readTemperature());
    display.print(" *C");
    //    Serial.print(bmp.readTemperature());



        display.setCursor(0,10);
    display.print("Pres = ");
     display.print(bmp.readPressure());
    display.print(" pa");
    
    display.setCursor(0,20);
    display.print("Alt = " );
    display.print(bmp.readAltitude());
    display.print(" meters");
  //  Serial.print(bmp.readAltitude());
  
    display.setCursor(0,20);
    display.print("PresSea= ");
    display.print(bmp.readSealevelPressure());
    display.print(" pa");
  //  Serial.print(bmp.readSealevelPressure());

    display.setCursor(0,30);
    display.print("Real altitude = ");
    display.print(bmp.readAltitude(101500));
    display.print(" meters");
   // Serial.print(bmp.readAltitude(101500));


      int chk = DHT.read11(pe.digitalRead(5));
   // display.setCursor(0,60);
    display.print("Temperature = ");
    display.print(DHT.temperature);
    display.print("Humidity = ");
    display.print(DHT.humidity);
#endif

  //if time = 0:00 then get eeprom time
  TimeVar storedTime;
  EEPROM.get(0, storedTime);
  if (storedTime != defaultTime)
  {
    remainingTime = storedTime;
  }
  else
  {
    remainingTime = defaultTime;
  }
  Serial.print("Countdown Time:");
  char buffer[15] = "";
  snprintf(buffer, sizeof(buffer), "%2d:%2d:%2d, ", remainingTime.hour, remainingTime.minute, remainingTime.second);
  Serial.print(buffer);
  Serial.println(remainingTime == defaultTime? "the default time." : "the stored time");
  
    display.display();
count=0;
}else{
count++;
}
// loop for input too to get faster timing.

    if ( activated == 0 ) {
      for( int i = 3; i < 7; i++ ){
     // i=1;
      if( pe.digitalRead(i) == 1 ){
        Serial.print("activated keypad \n" );
                activated=1;
        }

      }
    }
      
  if ( activated == 1 ) {
    
        if (countit >= 450) {
            activated=0;
            countit=0;
            Serial.print("deactivated keypad \n" );
         }

      for( int i = 3; i < 7; i++ ){
     // i=1;
      if( pe.digitalRead(i) == 1 ){
        Serial.print("Pin " );
        Serial.print(i);
        Serial.println(" is low.");
        }
      }
    if( pe.digitalRead(3) == 1 ) //pad 1 pin 3 temp up
      { pin3=1;
          temperature+=1;
     
          display.clearDisplay();
          display.display();
          display.setTextSize(0.5);
          display.setTextColor(WHITE);
          
          #ifdef BMP085
          display.setCursor(0,10);
          display.print("Temperature = ");
          display.print(bmp.readTemperature());
          display.print(" *C");
          display.display();
          #endif
      }
    if( pe.digitalRead(4) == 1 )
      { pin4=1;
      
      }
    if( pe.digitalRead(5) == 1 )
      { pin5=1;
      
      }
    if( pe.digitalRead(6) == 1 )//pad 4 pin 6 temp down
      { pin6=1;
                temperature-=1;
     
          display.clearDisplay();
          display.display();
          display.setTextSize(0.5);
          display.setTextColor(WHITE);
          
          #ifdef BMP085
          display.setCursor(0,10);
          display.print("Temperature = ");
          display.print(bmp.readTemperature());
          display.print(" *C");
          display.display();
          #endif
      }
   //active loop update eeprom
  if(millis() -  startTime > 20000UL && !updated)
  {
    TimeVar newTime = {1,20,30};
    EEPROM.put(0,newTime);
    Serial.println("stored time updated");
    updated = true;
  }
      countit++;
    delay(60); 
     
  }
  else{   delay(1060); //sleep loop update eeprom
    
    if(millis() -  startTime > 20000UL && !updated)
    {
      TimeVar newTime = {1,20,30};
      EEPROM.put(0,newTime);
      Serial.println("stored time updated");
      updated = true;
    }
  
  }
  


  
}
