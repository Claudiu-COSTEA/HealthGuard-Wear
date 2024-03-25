#include <ESP8266WiFi.h>

const char* ssid = "NumeleRețeleiWiFi";
const char* password = "ParolaWiFi";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conectare la WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectare la ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectat.");
  Serial.println("Adresa IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Aici poți adăuga codul tău
}
