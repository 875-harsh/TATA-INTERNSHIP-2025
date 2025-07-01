#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "Harsh";
const char* password = "jaishreeram454";

// ThingSpeak settings
const char* serverName = "http://api.thingspeak.com/update";
String apiKey = "VAYE4D6AMKT96ZEK";

// Potentiometer connected to GPIO 34 (ADC1_CH6)
const int potPin = 34;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;  // 10 seconds

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
      // Read analog value
      int adcValue = analogRead(potPin);
      float voltage = (adcValue / 4095.0) * 3.3;

      Serial.print("Voltage: ");
      Serial.print(voltage, 2);
      Serial.println(" V");

      // Prepare HTTP POST
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Prepare data to send
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
