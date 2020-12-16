#include <HCSR04.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>

HCSR04 sensor1(D0,D1);
HCSR04 sensor2(D3,D2);

const char* ssid = "Chuensooksri_2.4G";
const char* password = "178f420c";

AsyncWebServer server(80);

String getDistance() {
    float d_1 = sensor1.dist();
    float d_2 = sensor2.dist();
    return "{\"sensor_1\":\""+String(d_1)+"\",\"sensor_2\":\""+String(d_2)+"\"}";
  }

void setup() {
  // put your setup code here, to run once:
  {
    Serial.begin(115200);
  }
    // Initialize SPIFFS
  if (! SPIFFS.begin ()) {
    Serial.println ("An Error has occurred while mounting SPIFFS");
    return;
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
  }

  Serial.println(WiFi.localIP());
  
  // Route for web page
  server.on ("/", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send (SPIFFS, "/index.html");
  });
  server.on ("/beta.html", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send (SPIFFS, "/beta.html");
  });
  server.on ("/distance", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send_P (200, "text / plain", getDistance(). c_str ());
  });
  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin ();
}

void loop() {
  // put your main code here, to run repeatedly:
}
