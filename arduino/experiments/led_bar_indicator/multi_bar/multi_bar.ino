const uint8_t barLevelPin = 9;
const uint8_t selectorPins[5] = {8, 7, 6, 5, 4};
// const uint8_t values[5] = {26, 51, 77, 110, 128};
const uint8_t values[5] = {128,26,51,110,77};

void setup() {
  // Serial.begin(9600);
  pinMode(barLevelPin, OUTPUT);
  for (uint8_t pin : selectorPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

void loop() {
  for (uint8_t selected = 0; selected < 5; selected++) {
    analogWrite(barLevelPin, values[selected]);
    delay(8);
    digitalWrite(selectorPins[selected], LOW);
    delay(10);
    digitalWrite(selectorPins[selected], HIGH);
  }
}
