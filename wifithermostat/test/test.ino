/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>
//https://gist.github.com/Cyclenerd/7c9cba13360ec1ec9d2ea36e50c7ff77
const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server
    #include <DHT.h>
    #define DHTPIN 2     // Digital pin connected to the DHT sensor
     
    // Uncomment the type of sensor in use:
    #define DHTTYPE    DHT11     // DHT 11
    //#define DHTTYPE    DHT22     // DHT 22 (AM2302)
    //#define DHTTYPE    DHT21     // DHT 21 (AM2301)
     
    DHT dht(DHTPIN, DHTTYPE);
        // current temperature & humidity, updated in loop()
    float t = 0.0;
    float h = 0.0;

String responseHTML = "<!DOCTYPE html>"
  "<html lang=\"en\">"
  "<head>"
    "<meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<title>Internet of Bottles</title>"
    "<script type=\"text/javascript\">"
    "function changeChatText(text) {"
	"text = text.split(\"|\");"
"let ul = document.getElementById(\"chat\");"
	"ul.innerHTML = \"\";"
	"let disclaimer = document.getElementById(\"disclaimer\");"
	"if (text.length - 1 == 0) {"
		"disclaimer.style.display = '';"
		"disclaimer.textContent = \"Be the first one to leave a message\";"
	"return"
"} else {"
	"disclaimer.style.display = \"none\";"
"	}"
	// add messages one by one
"	for (i = 0; i < text.length - 1; i++) {"
"		let li = document.createElement(\"li\");"
"		li.appendChild(document.createTextNode(text[i]));"
"		ul.appendChild(li);"
"	}"
"}"

// get message file contents and call changeChatText
"function getText() {"
"	fetch(`/showText`).then(function (response) {"
	"	response.text().then(function (text) {"
	"		changeChatText(text)"
	"	})"
	"})"
"}"

// initialize global cache variable.
// we need this to compare write times of the message file
"var cache = ''"

// get last time chat was written to and syncronize if necessary.
// executed every second
"function sync() {"
"	setInterval(function getLastWrite() {"
	"	fetch(`/lastWrite`).then(function (response) {"
		"	response.text().then(function (text) {"
			"	if (cache !== text) {"
				"	cache = text"
			"		getText()"
			"	}"
		"	})"
		"})"
	"}, 1000)"
"}"

// start syncing on page load
"window.onload = sync();"

   "</script>"

  "</head>"
  "<body>"
  "<p>I'm just a stupid bottle with WiFi.</p>"

      "<h1>Chat</h1>"
    "<p id=\"disclaimer\">loading messages...</p>"
    "<ul id=\"chat\">"
    "</ul>"
    "<h1>Post Message</h1>"
    "<form action=\"sendText\" method=\"post\">"
        "<label for=\"nickname\">Nickname</label>"
        "<input name=\"nickname\" id=\"nickname\" type=\"text\" placeholder=\"anon\"></input>"
        "<label for=\"text\">Text*</label>"
        "<textarea id=\"text\" name=\"text\" cols=35 rows=\"4\" required=\"required\"></textarea>"
        "<p id=\"formDisclaimer\">Fields marked with * are required.</p>"
        "<input type=\"submit\" value=\"Send message\">"
    "</form>"
  "</body>"
  "</html>";
  

void setup() {
  // turn the LED on (HIGH is the voltage level)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
      Serial.begin(9600);
        dht.begin();
        
  // configure access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("IoT --- Free WiFi2"); // WiFi name
WiFi.setOutputPower(0.2); // this sets wifi to lowest power
  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}


    unsigned long previousMillis = 0;    // will store last time DHT was updated
     
    // Updates DHT readings every 10 seconds
    const long interval = 10000;


void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();

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
        delay(200);
}
