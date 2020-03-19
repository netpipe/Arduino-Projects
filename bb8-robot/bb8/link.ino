#include <LAudio.h>
#include <LBT.h>
#include <LBTClient.h>
#include <LBTServer.h>
#include <Servo.h>

int data_in;

int m1right=10;
int m1left=11;
int m2forward=5;
int m2backward=6;
int lighteffect=13;



int sound=0;
int servosignal=0;
int right=0;
int left=0;
int forward=0;
int backward=0;
int light=0;
String controlcmd;
String prevcontrolcmd;

Servo head;

void setup() {
  if(!LBTServer.begin((uint8_t*)"BB-8 Droid"))
 {
 return;
 }
  Serial.begin(9600); 
 
  pinMode(m1right, OUTPUT);
  pinMode(m1left, OUTPUT);
  pinMode(m2forward, OUTPUT);
  pinMode(m2backward, OUTPUT);  
  pinMode(13, OUTPUT);
  
  digitalWrite(m1right, LOW);
  digitalWrite(m1left, LOW);
  digitalWrite(m2forward, LOW);
  digitalWrite(m2backward, LOW);
  digitalWrite(13, LOW);

  head.attach(9);
 
  
}

void loop() {
 uint8_t buf[1];
 int bytesRead;
 if(LBTServer.connected())
 {
 while(true)
 {
 bytesRead = LBTServer.readBytes(buf, 1);
 if(!bytesRead)
 break;
 data_in = buf[0];
 controlcmd="";
 controlcmd+=char(data_in);
 control();
//  Serial.print(controlcmd);
 }
 delay(100);
 }
 else
 {
  digitalWrite(m1right, LOW);
  digitalWrite(m1left, LOW);
  digitalWrite(m2forward, LOW);
  digitalWrite(m2backward, LOW); 
 }
}


void control()
{
  forward=0;
  backward=0;
  left=0;
  right=0;
  if (controlcmd=="F"){
   forward = 1;   
  }
  else if (controlcmd=="B"){
    backward=1;
  }
  else if (controlcmd=="L") { 
    left=1;
  }
  else if (controlcmd=="R") {
    right=1;
  }
  else if (controlcmd=="G" || controlcmd=="I") {
    forward = 1;    
    if (controlcmd=="G"){
      left=1;      
    }
    else{
      right=1;      
    }
  }
  else if (controlcmd=="H" || controlcmd=="J") {  
    backward = 1;    
    if (controlcmd=="G"){
      left=1;      
    }
    else{
      right=1;      
    }
  }
   if (controlcmd=="W"){
   light = 1;   
  }
  else if (controlcmd=="w"){
    light=0;
  }
  
   if (controlcmd=="V"){
   sound = 1;   
  }
  else if (controlcmd=="v"){
    sound=0;
  }

      if (controlcmd=="X"){
   servosignal = 1;   
  }
  else if (controlcmd=="x"){
   servosignal = 0;
  }
  
  
  //Serial.println(controlcmd);
  
  if(prevcontrolcmd!=controlcmd)  
  {
    prevcontrolcmd=controlcmd;
//    Serial.println(right);
//    Serial.println(right);  
//    Serial.println(left);  
//    Serial.println(forward);  
//    Serial.println(backward);    


    if (servosignal==0)
    {
    head.write(95); 
  
    }else
    {
    head.write(120); 
   
    }
    
    if (right==0)
    {
    digitalWrite(m1right, LOW);  
    }else
    {
    digitalWrite(m1right, HIGH);  
    }
    
    if (left==0)
    {
    digitalWrite(m1left, LOW);  
    } else
    {
    digitalWrite(m1left, HIGH);  
    }
    
    if (forward==0)
    {
    digitalWrite(m2forward, LOW); 
    head.write(95); 
    }else
    {
    digitalWrite(m2forward, HIGH);  
    head.write(120);
    }
    
    if (backward==0)
    {
    digitalWrite(m2backward, LOW);  
    }else
    {
    digitalWrite(m2backward, HIGH);  
    }
   
    if (light==0)
    {
    digitalWrite(lighteffect, LOW);  
    }else
    {
    digitalWrite(lighteffect, HIGH);  
    }
    
    if (sound==0)
    {
    LAudio.begin();
    LAudio.setVolume(5);
    LAudio.playFile(storageSD,(char *)"BB8.mp3"); 
    }else
    {
    LAudio.stop(); 
    }
                     
  }
 
}
