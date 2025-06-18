volatile unsigned long lastMicros = 0;
volatile unsigned long intervalMicros = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT); // Digitalni pin 2 (prekid 0) za dolazne impulse
  attachInterrupt(digitalPinToInterrupt(2), measurePulseInterval, RISING);
}

void loop() {
  // Prikaz merenja svakih 100ms
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 100) {
    noInterrupts();
    unsigned long interval = intervalMicros;
    interrupts();
    
    Serial.print("Interval između impulsa: ");
    Serial.print(interval);
    Serial.println(" µs");
    lastPrint = millis();
  }
}

void measurePulseInterval() {
  unsigned long now = micros();
  intervalMicros = now - lastMicros;
  lastMicros = now;
}
