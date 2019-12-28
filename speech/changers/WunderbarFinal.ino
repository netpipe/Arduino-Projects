#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 3
#define DIO 4


// Pin Numbers
const int pressurePin = A0;
const int buttonPin = 8;
const int audioPin = 7;


// Rad pins (Voor opdracht keuze).
const int RadLedPin1 = 2;
const int RadLedPin2 = 5;
const int RadLedPin3 = 6;


// Result Led Pins (Nog dingen mee gebeuren ofzo)
const int ResultLedPin1 = 9;
const int ResultLedPin2 = 10;
const int ResultLedPin3 = 11;


int pressure;

// Timer gerelateerde variable.
int NumStep;
int MaxTime = 59;

int timeSec;
int timeMiliSec;
int tempTime;


// Glass Detect gerelteerde variable.
int pressureState;
int prevPressureState = 0;
int glassState;
int result;
bool glassLift;



// Button gerelateerde variable.
int buttonState;
bool start;
bool glassOnSpot;

TM1637Display display(CLK, DIO);


// Leds gerelateerde variable.
int randomInt;
int beginGewicht1 = 100;
int eindGewicht1 = 175;
int beginGewicht2 = 175;
int eindGewicht2 = 183;
int beginGewicht3 = 183;
int eindGewicht3 = 255;

int forLoopInt;


void setup() {  
  // Voor het doorgeven van informatie naar de serial monitor.
  Serial.begin(9600);
  
  // Hier word er aangegevn dat we een input krijgen van het pressure point inplaats van dat we er iets aan geven.
  pinMode(pressurePin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(audioPin, OUTPUT);

  // LedPin modes.
  pinMode(ResultLedPin1, OUTPUT);
  pinMode(ResultLedPin2, OUTPUT);
  pinMode(ResultLedPin3, OUTPUT);
  pinMode(RadLedPin1, OUTPUT);
  pinMode(RadLedPin2, OUTPUT);
  pinMode(RadLedPin3, OUTPUT);

  // Helderheid van de Timer Display
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
}


void loop() 
{
  
  pressure = analogRead(pressurePin);
  pressure = map(pressure, 0, 1023, 0, 255);
  buttonState = digitalRead(buttonPin);  
  pressureState = analogRead(pressurePin);
  pressureState = map(pressureState, 0, 1023, 0, 255);
  
  display.showNumberDecEx(timeSec,0x80>>3,true,2,0); //Display the Variable value; 
  display.showNumberDecEx(timeMiliSec,0,true,2,2);

  //Prints, weghalen/comenten wanneer klaar. (code werkt niet goed met alle prints actief)
  ////////////////////////////////////////
  //Serial.print("glassLift ");
  //Serial.print(glassLift);
  Serial.print(" pressure ");
  Serial.print(pressure);
  //Serial.print(" pressureState ");
  //Serial.println(pressureState);
  //Serial.print(" ");
  //Serial.print(randomInt);
  Serial.print(" result ");
  Serial.println(result);
  //Serial.print(" timeMiliSec ");
  //Serial.print(timeMiliSec);
  //Serial.print(" timeSec ");
  //Serial.println(timeSec);
  /////////////////////////////////////////

  // Checkt of knop word ingedrukt en start/reset de game.
  if(buttonState == HIGH)
  {
    glassState = 0;
    digitalWrite(audioPin, LOW); 
    Start();          // Verwijst naar de Start functie.
    GlassDetect();    // Verwijst naar de GlassDetect functie.
    randomInt = random(1,4);
    Leds();
  }
  
  if(start == true)
  {    
    Leds();    
    if(glassState == 2)
    {
      TimeKeeper();
    }
    else if(glassState <= 1)
    {
      timeSec = 0;
      timeMiliSec = 0;
    }

    if(glassState == 1)
    {      
      tempTime = millis() / 10;
    }
    
    //Maakt de druksensor een HIGH, LOW output.
    //Belangerijk voor de start en stop van de timer.
    //Niet verwijderen.
    if(pressureState >0)
    {
      pressureState = 1;
    }
    else
    {
      pressureState = 0;
    }
        
    // Checken voor het verwijderen van het glas van de plaats.
    // Hiermee word de timer stilgezet tot de resetknop is ingedrukt
    if(pressureState != prevPressureState)
    {
      glassState ++;
      prevPressureState = pressureState;    
    }
    
    if(glassState == 3)
    {
      int wait = 0;
      wait ++;
      while(wait < 1000)
      {
        Serial.println(wait);
        wait ++;
        pressure = analogRead(pressurePin);
        pressure = map(pressure, 0, 1023, 0, 255);
        if(wait >= 1000)
        {  
          glassState++;
          glassLift = false;
        }      
      }
    }


    if(glassState == 4)
    {        
      result = pressure;
      glassState++;
    }
  }
}


// Start shit.
void Start()
{
  result = 0;
  start = true;
  glassLift = true;
  digitalWrite(ResultLedPin1, LOW);
  digitalWrite(ResultLedPin2, LOW);
  digitalWrite(ResultLedPin3, LOW);
  if(glassState >=3)
  {   
    glassState = 0;
  }
}


// Houdt de tijd bij en stuurt dit door naar de Display.
void TimeKeeper()
{
  if(timeSec <= MaxTime)
  {
    timeMiliSec = (millis() / 10) - tempTime;   //Hiermee word bij de start van de timer iederekeer de vorige waarde eraf gehaald.
                                                //Zo start het altijd bij 0.
    if(timeMiliSec >= 100)
    {
      timeSec++;
      tempTime = millis() / 10;
    }
  }
}


void GlassDetect()
{
  if(pressureState == 0)
  {
    glassState = 0;
  }
  else
  {
    glassState = 1;
  }
}


void Leds()
{
  if(buttonState == HIGH)
  {
    for(forLoopInt=0; forLoopInt<12; forLoopInt++)
    { 
    digitalWrite(RadLedPin1, HIGH);
    delay(50);
    digitalWrite(RadLedPin1, LOW);
    digitalWrite(RadLedPin2, HIGH);
    delay(50);
    digitalWrite(RadLedPin2, LOW);
    digitalWrite(RadLedPin3, HIGH);
    delay(50);
    digitalWrite(RadLedPin3, LOW);   
    }
  }
  
  if(forLoopInt == 12)
  {
    if(randomInt == 1)
    {
      digitalWrite(RadLedPin1, HIGH);
    }
    if(randomInt == 2)
    {
      digitalWrite(RadLedPin2, HIGH);
    }
    if(randomInt == 3)
    {
      digitalWrite(RadLedPin3, HIGH);
    }
  }

  if(glassState >=2)
  {
    if(result >= beginGewicht1 && result <= eindGewicht1)
    {
      digitalWrite(ResultLedPin1, HIGH);
      if(randomInt == 1)
      {
        digitalWrite(audioPin, HIGH);      
      }
    }
    else
    {
      digitalWrite(ResultLedPin1, LOW);
    }
  
    if(result >= beginGewicht2 && result <= eindGewicht2)
    {
      digitalWrite(ResultLedPin2, HIGH);
      if(randomInt == 2)
      {
        digitalWrite(audioPin, HIGH);      
      }    
    }
    else
    {
      digitalWrite(ResultLedPin2, LOW);
    }
  
    if(result >= beginGewicht3 && result <= eindGewicht3)
    {
      digitalWrite(ResultLedPin3, HIGH);
      if(randomInt == 3)
      {
        digitalWrite(audioPin, HIGH);      
      }
    }
    else
    {
      digitalWrite(ResultLedPin3, LOW);
    }
  }
}

