#include <ESP8266WiFi.h>

// Global Variables
const char *ssid         = "WuXD";
const char *password     = "5p7i2g3h";

void setup()
{
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  
}
