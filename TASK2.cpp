#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Harsh";
const char* password = "jaishreeram454";
const char* serverName = "http://api.thingspeak.com/update";
String apiKey = "VAYE4D6AMKT96ZEK";
const int potPin = 34;
unsigned long lastTime = 0;
unsigned long timerDelay = 10000; 

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting sensor read and ThingSpeak upload every 10 seconds...");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      int adcValue = analogRead(potPin);
      float voltage = (adcValue / 4095.0) * 3.3;
      Serial.print("Voltage: ");
      Serial.print(voltage, 2);
      Serial.println(" V");
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(voltage, 2);
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200) {
        Serial.println("Data posted to ThingSpeak successfully.");
      } else {
        Serial.println("Error posting data.");
      }
      http.end(); 
    } else {
      Serial.println("WiFi Disconnected. Reconnecting...");
    }
    lastTime = millis();
  }
}
