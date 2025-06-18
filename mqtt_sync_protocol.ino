#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SSID";
const char* pass = "PASSWORD";
const char* mqttServer = "192.168.1.10";

WiFiClient espClient;
PubSubClient client(espClient);

volatile unsigned long lastMicros = 0, deltaMicros = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), onPulse, RISING);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(100);
  client.setServer(mqttServer, 1883);
}

void loop() {
  if (!client.connected()) client.connect("ESP32_Client");
  client.loop();
  static unsigned long lastPub = 0;
  if (millis() - lastPub >= 1000) {
    client.publish("etaloni/interval", String(deltaMicros).c_str());
    lastPub = millis();
  }
}

void onPulse() {
  unsigned long now = micros();
  deltaMicros = now - lastMicros;
  lastMicros = now;
}
