// Experiment-3: Send DHT11 humidity and temperature data to ThingSpeak using ESP8266

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define DHTPIN D3       // Pin connected to DHT11
#define DHTTYPE DHT11   // Sensor type

const char* ssid = "wifi_name";
const char* password = "password";

unsigned long ch_id = xxxxxx;  // ThingSpeak Channel ID
const char* apiKey = "yyyyyyyy"; // ThingSpeak Write API Key

DHT dht(DHTPIN , DHTTYPE);
WiFiClient client;

void setup(){
  Serial.begin(9600);
  dht.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop(){
  float h = dht.readHumidity();       // Read humidity
  float t = dht.readTemperature();    // Read temperature

  // Check if sensor reading failed
  if (isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to ThingSpeak fields
  ThingSpeak.setField(1, h);   // Humidity
  ThingSpeak.setField(2, t);   // Temperature

  int httpCode = ThingSpeak.writeFields(ch_id, apiKey);

  // Check if data upload was successful
  if(httpCode == 200){
    Serial.println("Channel write successful");

    Serial.print("Humidity: ");
    Serial.print(h);

    Serial.print("%\nTemperature: ");
    Serial.print(t);
    Serial.println("Deg._C\n");
  }else{
    Serial.println("Problem writing to channel");
  }

  delay(20000); // ThingSpeak minimum update interval
}
