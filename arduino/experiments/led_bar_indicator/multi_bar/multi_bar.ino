const uint8_t barLevelPin = 9;
const uint8_t selectorPins[5] = {8, 7, 6, 5, 4};
const uint8_t values[5] = {26, 51, 77, 110, 128};

void setup() {
  // Serial.begin(9600);
  pinMode(barLevelPin, OUTPUT);
  for (uint8_t pin : selectorPins) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  for (uint8_t selected = 0; selected < 5; selected++) {
    delay(100);
    for (uint8_t pin = 0; pin < 5; pin++) {
        digitalWrite(selectorPins[pin], HIGH);
    }

    analogWrite(barLevelPin, values[selected]);
    // analogWrite(barLevelPin, 0);

    for (uint8_t pin = 0; pin < 5; pin++) {

      if (pin == selected) {
        digitalWrite(selectorPins[pin], LOW);
      } else {
        digitalWrite(selectorPins[pin], HIGH);
      }

    }

    
  }
}
