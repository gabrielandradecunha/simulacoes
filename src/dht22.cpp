#include "DHTesp.h"

const int DHT_PIN = 13;
DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Testando");
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Umidade: " + String(data.humidity, 1) + "%");
  Serial.println("************************************************");
  delay(2000); 
}
