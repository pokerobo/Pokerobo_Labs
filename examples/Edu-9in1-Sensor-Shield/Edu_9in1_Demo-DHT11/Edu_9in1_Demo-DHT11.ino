#include <DHT.h>

const int dht11Pin = 4;

DHT dht(dht11Pin, DHT11);

void setup() {
  Serial.begin(57600);
  dht.begin();
}

void loop() {
  // Read temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Show temperature and humidity to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000);
}
