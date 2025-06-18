#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT config
const char* ssid = "your_ssid";
const char* password = "your_password";
const char* mqtt_server = "broker_address";

WiFiClient espClient;
PubSubClient client(espClient);

const int counterPins[] = {D1, D2, D3, D4, D5, D6, D7}; // Q0-Q6
const int pinCount = sizeof(counterPins) / sizeof(counterPins[0]);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    client.connect("CMOS_Bridge");
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  for (int i = 0; i < pinCount; i++) {
    pinMode(counterPins[i], INPUT);
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Read Q outputs as binary
  int countValue = 0;
  for (int i = 0; i < pinCount; i++) {
    countValue |= (digitalRead(counterPins[i]) << i);
  }

  // Create JSON payload
  StaticJsonDocument<200> doc;
  doc["counter_value"] = countValue;
  doc["timestamp"] = millis();

  char buffer[256];
  serializeJson(doc, buffer);
  client.publish("cmos/timing", buffer);

  delay(1000);
}
