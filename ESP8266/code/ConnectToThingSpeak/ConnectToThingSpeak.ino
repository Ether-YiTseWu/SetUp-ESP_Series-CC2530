#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Wi-fi
const char* ssid      = "WuXD";
const char* password  = "5p7i2g3h";

// ThingSpeak
const char* apiKey = "I3C5EFUZX8DEUFHA";
const char* resource = "/update?api_key=";
const char* server = "api.thingspeak.com";

// Soil pin
const int soilPin = A0;

WiFiClient client;

void setup()
{
  // Initializing serial port for debugging purposes
  Serial.begin(9600);

  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop()
{
  int soil[3] = {1, 2, 3};
  soil[0] = analogRead(soilPin);
  Serial.print("Soil moisure : ");
  Serial.println(soil[0]);

  Serial.print("Connecting to ");
  Serial.print(server);

  // Use port 80 to connect
  if (client.connect(server, 80))
    Serial.println(F("connected"));
  else
  {
    Serial.println(F("connection failed"));
    return;
  }

  Serial.print("Request resource: ");
  Serial.println(resource);
  client.print(String("GET ") + resource + apiKey + "&field1=" + soil[0] +
               " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" +
               "Connection: close\r\n\r\n");

  if (!client.available())
    Serial.println("No response, going back to sleep");
  while (client.available())
    Serial.write(client.read());

  Serial.println("\nclosing connection");
  client.stop();

  // 1 data / 5 min
  delay(300000);
}
