#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// ===== CONFIG Wi-Fi =====
const char* ssid = "wifi nome";
const char* password = "senha";

// ===== CONFIG MQTT =====
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* topic_temp = "teste/dht22/temperatura";
const char* topic_umid = "teste/dht22/umidade";

// ===== DHT22 =====
const int DHT_PIN = 13;
DHTesp dhtSensor;

// ===== Objetos WiFi e MQTT =====
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Conectando em ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32_DHT22_TESTE")) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  if (!isnan(data.temperature) && !isnan(data.humidity)) {
    Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
    Serial.println("Umidade: " + String(data.humidity, 1) + "%");
    Serial.println("************************************************");

    client.publish(topic_temp, String(data.temperature, 2).c_str());
    client.publish(topic_umid, String(data.humidity, 1).c_str());
  } else {
    Serial.println("Falha ao ler do sensor DHT22");
  }

  delay(2000);
}
