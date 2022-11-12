// PopupChat - a one-screen system to share things locally with your friends via WIFI
// based on: Captive Portal by: M. Ray Burnette 20150831
// homo est bulae
#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>
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

  int i=0;
  int count=0;
int countit=0;
int activated=1;
bool pin3,pin4,pin5,pin6;
int temperature;

TimeVar remainingTime;
const TimeVar defaultTime = {0, 10, 30};  // program default time is 00:10:30 , zero hours, ten minutes and thirty seconds
unsigned long startTime = 0;
bool updated = false;

    #include <DHT.h>
    #define DHTPIN 4     // Digital pin connected to the DHT sensor
     
    // Uncomment the type of sensor in use:
    #define DHTTYPE    DHT11     // DHT 11
    //#define DHTTYPE    DHT22     // DHT 22 (AM2302)
    //#define DHTTYPE    DHT21     // DHT 21 (AM2301)
     
    DHT dht(DHTPIN, DHTTYPE);
        // current temperature & humidity, updated in loop()
    float t = 0.0;
    float h = 0.0;
// config
#define CHATNAME "Anonymous Chatroom"
#define BLURB "esp8266 chat"
#define FOOTERTHING "https://github.com/netpipe/Arduino-Projects/tree/master/8266chat"
#define INDEXTITLE "Howdy friend!"
#define INDEXBANNER "wireless chat <a href=/faq>..</a>"
#define POSTEDTITLE "Message sent!"
#define POSTEDBANNER "OK, you should be good to go. Your message will stay live for a short time - perhaps a couple of days at most, until the wee server is rebooted. Here it is again:"
const String FAQ = "test chatroom<br/>";

const char *password = "";


// boring
#define VER "R1"
const byte HTTP_CODE = 200; // nyi? 511; // rfc6585
const byte DNS_PORT = 53;  // Capture DNS requests on port 53
const byte TICK_TIMER = 1000;
const byte ACTIVITY_DURATION = 60 * TICK_TIMER; // how many seconds should the LED stay on after last visit?
const byte ACTIVITY_LED = 2;
const byte ACTIVITY_REVERSE = 1; // turn off when active, not on.. needed for me
IPAddress APIP(10, 10, 10, 1);    // Private network for server
// state:
String allMsgs="<i>initialized</i>";
unsigned long bootTime=0, lastActivity=0, lastTick=0, tickCtr=0; // timers
DNSServer dnsServer; ESP8266WebServer webServer(80); // standard api servers
void em(String s){ Serial.print(s); } 
void emit(String s){ Serial.println(s); } // debugging
String input(String argName) {
  String a=webServer.arg(argName);
  a.replace("<","&lt;");a.replace(">","&gt;");
  a.substring(0,200); return a; }
String quote() { 
  const byte nquotes=6;
  String quotes[nquotes]={
    "Blushing is the color of virtue -Diogenes of Synope", 
    "A bear can run as fast as a horse",
    "Homo homini lupus est - man is a wolf to fellow man",
    "When you rub it then you do it.",
        "A bing can also be a ding.",
            "Then and now are ways to view things.",
            
  };
  return quotes[millis() / 1000 / 60 / 60 % nquotes];
}
String footer() { return 
  "</div><div class=q><label>Quote of the hour:</label>"+quote()+"</div>"
  "<div class=com>SourceCode: " FOOTERTHING "</div>"
  "<img src=\"data:image/png;base64,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\">"

  "<div class=by>" VER "</div></body></html>"; }
String header(String t) {
  String a = String(CHATNAME);
  String CSS = "article { background: #32f2f2; padding: 1em; }" 
    "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
    "div { padding: 0.5em; }"
    "h1 { margin: 0.5em 0 0 0; padding: 0; }"
    "input { border-radius: 0; }"
    "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
    "nav { background: #3b3570; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
    "nav b { display: block; font-size: 1.2em; margin-bottom: 0.5em; } "
    "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
    "<head><meta http-equiv=\"refresh\" content=\"100\"><title>"+a+" :: "+t+"</title>"
    "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
    "<style>"+CSS+"</style></head>"
    "<body><nav><b>"+a+"</b> "+BLURB+"</nav><div></div><div>";
  emit("header - "+t);
  emit(h);
  return h; }

  String header2(String t) {
  String a = String(CHATNAME);
  String CSS = "article { background: #f2f2f2; padding: 1em; }" 
    "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
    "div { padding: 0.5em; }"
    "h1 { margin: 0.5em 0 0 0; padding: 0; }"
    "input { border-radius: 0; }"
    "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
    "nav { background: #3b3570; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
    "nav b { display: block; font-size: 1.2em; margin-bottom: 0.5em; } "
    "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
    "<head><meta http-equiv=\"refresh\" content=\"10; URL=http://10.10.10.1\"/><title>"+a+" :: "+t+"</title>"
    "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
    "<style>"+CSS+"</style></head>"
    "<body><nav><b>"+a+"</b> "+BLURB+"</nav><div></div><div>";
  emit("header - "+t);
  emit(h);
  return h; }
    
String faq() {
  return header("frequently asked questions") + FAQ + footer();
}
String index() {
  return header(INDEXTITLE) + "<div>" + "</div><div><ol>"+allMsgs+
    "</ol></div><div><form action=/post method=post><label>Post new message:</label>"+
    "<textarea name=m></textarea><br/><input type=submit value=send></form>" + footer();
}

String index2() {
    String msg=input("m"); allMsgs="<li>"+msg+"</li>"+allMsgs;
  emit("posted: "+msg); 
  return header2(INDEXTITLE) + "<div>"  + "</div><div><ol>"+allMsgs+
    "</ol></div><div><form action=/post method=post><label>Post new message:</label>"+
    "<textarea name=m></textarea><br/><input type=submit value=send></form>" + footer();
}
String posted() {
  String msg=input("m"); allMsgs="<li>"+msg+"</li>"+allMsgs;
  emit("posted: "+msg); 
  return header(POSTEDTITLE) + POSTEDBANNER + "<article>"+msg+"</article><a href=/>Back to index</a>" + footer();
}
void setup() {
  Serial.begin(115200); 
  emit("setup"); 
   pinMode(5, OUTPUT); 
  bootTime = lastActivity = millis();
  pinMode(ACTIVITY_LED, OUTPUT); led(1);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
     WiFi.softAP(CHATNAME, password);
  //WiFi.softAP(CHATNAME);
  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.on("/post",[]() { webServer.send(HTTP_CODE, "text/html", index2()); });
  webServer.on("/faq",[]() { webServer.send(HTTP_CODE, "text/html", faq()); });
  webServer.onNotFound([]() { lastActivity=millis(); webServer.send(HTTP_CODE, "text/html", index()); });
  webServer.begin();
  WiFi.setOutputPower(0.2);
}
void led(byte p){
  byte on=p^ACTIVITY_REVERSE; emit("led"+String(on));
  digitalWrite(ACTIVITY_LED, on ? HIGH : LOW);
}
void tick() {
  String tickCs=String(tickCtr++); // emit("tick #"+tickCs+" @"+String(millis()));
  if ((millis() - lastActivity) < ACTIVITY_DURATION) {
    em("+"); led(1);
  } else {
    em("-"); lastActivity = 0; led(0);
  }
}


    unsigned long previousMillis = 0;    // will store last time DHT was updated
     
    // Updates DHT readings every 10 seconds
    const long interval = 10000;
void loop() { 
  if ((millis()-lastTick)>TICK_TIMER) {lastTick=millis(); tick();} 
  dnsServer.processNextRequest(); webServer.handleClient();
  
  
        unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        // save the last time you updated the DHT values
        previousMillis = currentMillis;
        // Read temperature as Celsius (the default)
        float newT = dht.readTemperature();
        // Read temperature as Fahrenheit (isFahrenheit = true)
        //float newT = dht.readTemperature(true);
        // if temperature read failed, don't change t value
        if (isnan(newT)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
          t = newT;
          Serial.println(t);
        }
        // Read Humidity
        float newH = dht.readHumidity();
        // if humidity read failed, don't change h value
        if (isnan(newH)) {
          Serial.println("Failed to read from DHT sensor!");
        }
        else {
          h = newH;
          Serial.println(h);
        }
      }


  
if ( count > 10 ){

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

count=0;
}else{
count++;
}
// loop for input too to get faster timing.

    if ( activated == 0 ) {
//      for( int i = 3; i < 7; i++ ){
//     // i=1;
//      if( pe.digitalRead(i) == 1 ){
//        Serial.print("activated keypad \n" );
//                activated=1;
//        }
//
//      }
//    }
//      

   //active loop update eeprom
  if(millis() -  startTime > 20000UL && !updated)
  {
    TimeVar newTime = {1,20,30};
    EEPROM.put(0,newTime);
    Serial.println("stored time updated");
    updated = true;
  }
      countit++;
    delay(10); 
     
  }  else{   delay(1060); //sleep loop update eeprom
    
    if(millis() -  startTime > 20000UL && !updated)
    {
      TimeVar newTime = {1,20,30};
      EEPROM.put(0,newTime);
      Serial.println("stored time updated");
      updated = true;
    }
  
  }

      
        delay(200);
        
         }
  