// Selektori SW2 (frekvencija)
const int sw2_s0 = 2;
const int sw2_s1 = 3;
const int sw2_s2 = 4;

// Selektori SW3 (vremenski prozori)
const int sw3_s0 = 5;
const int sw3_s1 = 6;
const int sw3_s2 = 7;
const int sw3_s3 = 8;
const int sw3_s4 = 9;

// Ulaz za vremenski impuls
const int signalPin = 10;

void setup() {
  pinMode(sw2_s0, OUTPUT);
  pinMode(sw2_s1, OUTPUT);
  pinMode(sw2_s2, OUTPUT);

  pinMode(sw3_s0, OUTPUT);
  pinMode(sw3_s1, OUTPUT);
  pinMode(sw3_s2, OUTPUT);
  pinMode(sw3_s3, OUTPUT);
  pinMode(sw3_s4, OUTPUT);

  pinMode(signalPin, INPUT);

  // Npr. izaberi 10 Hz (bin 101) i 3. prozor (bin 00011)
  selectFrequency(0b101); // SW2
  selectWindow(0b00011);  // SW3
}

void loop() {
  if (digitalRead(signalPin) == HIGH) {
    // Meri impuls, koristi micros() ili interrupt
  }
}

void selectFrequency(byte val) {
  digitalWrite(sw2_s0, val & 0x01);
  digitalWrite(sw2_s1, (val >> 1) & 0x01);
  digitalWrite(sw2_s2, (val >> 2) & 0x01);
}

void selectWindow(byte val) {
  digitalWrite(sw3_s0, val & 0x01);
  digitalWrite(sw3_s1, (val >> 1) & 0x01);
  digitalWrite(sw3_s2, (val >> 2) & 0x01);
  digitalWrite(sw3_s3, (val >> 3) & 0x01);
  digitalWrite(sw3_s4, (val >> 4) & 0x01);
}
