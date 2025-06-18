volatile unsigned long lastTime = 0;
volatile unsigned long deltaTime = 0;

void setup() {
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), onPulse, RISING);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Interval između impulsa (µs): ");
  Serial.println(deltaTime);
  delay(1000);
}

void onPulse() {
  unsigned long now = micros();
  deltaTime = now - lastTime;
  lastTime = now;
}
