// Task-1: Read humidity and temperature using DHT11 sensor

#include <DHT.h>

#define DHTPIN D1      // Pin where DHT11 is connected
#define DHTTYPE DHT11  // Sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  	Serial.begin(115200); // Start serial communication
  	dht.begin();          // Initialize DHT sensor
}

void loop()
{
  	float humidity = dht.readHumidity();        // Read humidity
  	float temperature = dht.readTemperature();  // Read temperature

  	// Check if reading failed
  	if (isnan(humidity) || isnan(temperature))
	{
    		Serial.println("failed to read from DHT sensor");
    		return;
  	}

  	// Print sensor values
  	Serial.print("Humidity:_");
  	Serial.print(humidity);
  	Serial.print("%, Temperature:_");
  	Serial.print(temperature);
  	Serial.println("Deg._C");

  	delay(2000); // Wait 2 seconds before next reading
}
