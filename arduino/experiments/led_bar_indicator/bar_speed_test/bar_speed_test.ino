const uint8_t ledPin = 9;
const uint8_t switchPin = 8;
const uint16_t myDelay = 10;



void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
  randomSeed(analogRead(0)); // Seed the random number generator with an analog input value
}

void loop() {
  analogWrite(ledPin, 255);
  delay(myDelay);
  analogWrite(ledPin, 0);
  delay(myDelay);
}
