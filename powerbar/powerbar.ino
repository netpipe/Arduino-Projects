/*
 *      
 *  www.HowToMechatronics.com
 *  http://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/
 */

//Thermistor
int ThermistorPin = 7;
int Vo;
float R1 = 15000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

 
//Sensors
int lightSensor = A0;
int pirSensor = A2;
int relayInput = A4 ;

void setup() {
  pinMode(ThermistorPin, INPUT);
  pinMode(lightSensor, INPUT);
  pinMode(pirSensor, INPUT);
  pinMode(relayInput, OUTPUT);  
    Serial.begin (115200);

}

void loop() {

//Thermistor
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C"); 

  
  //Sensors
  int sensorValue = digitalRead(pirSensor);
   // Serial.print (sensorValue);
  int sensorValue2 = analogRead(lightSensor);
  Serial.print (sensorValue2);
  Serial.print ("\n");
  delay(100);
  
  if (sensorValue == 1) {
   // digitalWrite(relayInput, LOW); // The Relay Input works Inversly
  } else{
    //digitalWrite(relayInput, HIGH);
  }
  
}
