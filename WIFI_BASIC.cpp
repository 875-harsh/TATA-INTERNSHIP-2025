#include <Arduino.h>
#include <WiFi.h>
int led1 = 27;
int led2 = 21;
int retry=0;
const char *ssid = "Harsh";
const char *password = "jaishreeram454";

void initWiFi()
{
  WiFi.mode(WIFI_STA); // Set Wi-Fi Mode as station
}
void startWifi()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".......");
    delay(1000);
    if((WiFi.status() != WL_CONNECTED)&& retry<5){
      WiFi.begin(ssid, password);
      delay(1000);
    }
    else{
      break;
    }
    retry++;
  }

  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT); // Initialize the LED pin as an output
  Serial.begin(115200);
  initWiFi();
}

void loop()
{
  startWifi();
  if (WiFi.isConnected())
  {
    Serial.println("WiFi is connected");
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
  }
  else
  {
    Serial.println("WiFi is not connected");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  delay(2000);
}