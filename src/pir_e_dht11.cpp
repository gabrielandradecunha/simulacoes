#include "DHTesp.h"

int pirPino = 4;
const int DHT_PIN = 2;
DHTesp dhtSensor;

void setup() {
  pinMode(pirPino, INPUT);
  Serial.begin(115200);
  Serial.println("Testando");
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
}

void loop() {
  int motionDetected = digitalRead(pirPino);
  if (motionDetected == HIGH) {
    Serial.println("Movimento detectado");
  } else {
    Serial.println("Sem movimento");
  }

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Umidade: " + String(data.humidity, 1) + "%");
  Serial.println("************************************************");
  
  delay(2000);
}
