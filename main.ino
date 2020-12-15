#include <HCSR04.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

int trig = D1;
int echo = D2;

HCSR04 hc(trig,echo);

const char* ssid = "Chuensooksri_2.4G";
const char* password = "178f420c";

AsyncWebServer server(80);

String getDistance() {
    float d = hc.dist();
    return String(d);
  }

void setup() {
  // put your setup code here, to run once:
  {
    Serial.begin(9600);
  }
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
  }

  Serial.println(WiFi.localIP());
  
  server.on ("/distance", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send_P (200, "text / plain", getDistance(). c_str ());
  });

  server.begin ();
}

void loop() {
  // put your main code here, to run repeatedly:
}
