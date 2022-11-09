    /*********
      Rui Santos
      Complete project details at https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/
     
      Permission is hereby granted, free of charge, to any person obtaining a copy
      of this software and associated documentation files.
      The above copyright notice and this permission notice shall be included in all
      copies or substantial portions of the Software.
    *********/
     
    // Import required libraries
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <Hash.h>
    #include <ESPAsyncTCP.h>
    #include <ESPAsyncWebServer.h>
    #include <Adafruit_Sensor.h>
    #include <DHT.h>
     
    const char* ssid     = "ESP8266-Access-Point";
    const char* password = "123456789";
     
    #define DHTPIN 2     // Digital pin connected to the DHT sensor
     
    // Uncomment the type of sensor in use:
    #define DHTTYPE    DHT11     // DHT 11
    //#define DHTTYPE    DHT22     // DHT 22 (AM2302)
    //#define DHTTYPE    DHT21     // DHT 21 (AM2301)
     
    DHT dht(DHTPIN, DHTTYPE);
     
    // current temperature & humidity, updated in loop()
    float t = 0.0;
    float h = 0.0;
     
    // Create AsyncWebServer object on port 80
    AsyncWebServer server(80);
     
    // Generally, you should use "unsigned long" for variables that hold time
    // The value will quickly become too large for an int to store
    unsigned long previousMillis = 0;    // will store last time DHT was updated
     
    // Updates DHT readings every 10 seconds
    const long interval = 10000;
     
    const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        html {
         font-family: Arial;
         display: inline-block;
         margin: 0px auto;
         text-align: center;
        }
        h2 { font-size: 3.0rem; }
        p { font-size: 3.0rem; }
        .units { font-size: 1.2rem; }
        .dht-labels{
          font-size: 1.5rem;
          vertical-align:middle;
          padding-bottom: 15px;
        }
      </style>
    </head>
    <body>
    <img src="data:image/png;base64,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">
      <h2>ESP8266 DHT Server</h2>
      <p>
        <span class="dht-labels">Temperature</span>
        <span id="temperature">%TEMPERATURE%</span>
        <sup class="units">°C</sup>
      </p>
      <p>
        <span class="dht-labels">Humidity</span>
        <span id="humidity">%HUMIDITY%</span>
        <sup class="units">%</sup>
      </p>
    </body>
    <script>
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("temperature").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/temperature", true);
      xhttp.send();
    }, 10000 ) ;
     
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("humidity").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/humidity", true);
      xhttp.send();
    }, 10000 ) ;
    </script>
    </html>)rawliteral";
     
    // Replaces placeholder with DHT values
    String processor(const String& var) {
      //Serial.println(var);
      if (var == "TEMPERATURE") {
        return String(t);
      }
      else if (var == "HUMIDITY") {
        return String(h);
      }
      return String();
    }
     
    void setup() {
      // Serial port for debugging purposes
      Serial.begin(9600);
      dht.begin();
     
      Serial.print("Setting AP (Access Point)…");
      // Remove the password parameter, if you want the AP (Access Point) to be open
      WiFi.softAP(ssid, password);
     
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);
     
      // Print ESP8266 Local IP Address
      Serial.println(WiFi.localIP());
     
      // Route for root / web page
      server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send_P(200, "text/html", index_html, processor);
      });
      server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send_P(200, "text/plain", String(t).c_str());
      });
      server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send_P(200, "text/plain", String(h).c_str());
      });
     
     
      //https://www.esp8266.com/viewtopic.php?f=32&t=13496
      WiFi.setOutputPower(0.2); //20.5 max
     
      // Start server
      server.begin();
    }
     
    void loop() {
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
    }


