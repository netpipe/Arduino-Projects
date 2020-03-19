//-------www<electronics-project-hub>com--------//

//https://electronics-project-hub.com/3-phase-sine-wave-generator-code-arduino/
//https://electronics-project-hub.com/three-phase-inverter-circuit-diagram/
#include <math.h>
int Output1 = 11;
int Output2 = 10;
int Output3 = 9;
int potVal = 0;
float A = 0;
float B = 0.104;
int Freq_IN = A0;
int var1 = 0;
int var2 = 0;
int var3 = 0;
int var4 = 0;
int var5 = 0;
int var6 = 0;
float Phase1 = 2 * PI / 3;
float Phase2 = 4 * PI / 3;
float Phase3 = 2 * PI;
boolean toggle = true; // true = Enabling Serial Plotter Output
void setup()
{
  Serial.begin(9600);
  pinMode(Output1, OUTPUT);
  pinMode(Output2, OUTPUT);
  pinMode(Output3, OUTPUT);
  pinMode(Freq_IN, INPUT);
}
void loop()
{
  A += B;
  analogWrite(Output1, var1);
  analogWrite(Output2, var2);
  analogWrite(Output3, var3);
  if (toggle == true)
  {
    Serial.print(var1);
    Serial.print(" ");
    Serial.print(var2);
    Serial.print(" ");
    Serial.println(var3);
  }
  var4 = 126 * sin(A + Phase1);
  var1 = var4 + 128;
  var5 = 126 * sin(A + Phase2);
  var2 = var5 + 128;
  var6 = 126 * sin(A + Phase3);
  var3 = var6 + 128;
  if (A >= 2 * PI)
  {
    A = 0;
  }
  potVal = analogRead(Freq_IN);
  delay(potVal);
}
//-------www<electronics-project-hub>com--------//
