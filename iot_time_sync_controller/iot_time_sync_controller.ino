volatile unsigned long lastMicros = 0;
volatile unsigned long intervalMicros = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), onPulse, RISING);
}

void onPulse() {
  unsigned long now = micros();
  intervalMicros = now - lastMicros;
  lastMicros = now;
}

void loop() {
  Serial.println(intervalMicros);
  delay(1000);
}
