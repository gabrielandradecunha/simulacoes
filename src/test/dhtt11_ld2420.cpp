#include <SoftwareSerial.h>
#define RX_PIN 10
#define TX_PIN 11
SoftwareSerial ld2420Serial(RX_PIN, TX_PIN);

#include "DHTesp.h"
const int DHT_PIN = 13;
DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  ld2420Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  Serial.println("Sistema iniciado: LD2420 + DHT22");
}

void loop() {
  if (ld2420Serial.available()) {
    String sensorData = ld2420Serial.readString();
    Serial.println("LD2420 -> " + sensorData);
  }

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Umidade: " + String(data.humidity, 1) + "%");
  Serial.println("===================================");
  delay(2000);
}
