const uint8_t barLevelPin = 9;
const uint8_t selectorPins[3] = {13, 12, 8};
// const uint8_t values[5] = {26, 51, 77, 110, 128};
const uint8_t values[5] = {1, 2, 3, 4, 5};
const uint8_t mappingValues[11] = {0, 29, 55, 78, 102, 128, 153, 179, 204, 230, 255};

void setup()
{
  Serial.begin(9600);
  pinMode(barLevelPin, OUTPUT);
  for (uint8_t pin : selectorPins)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  TCCR1B = TCCR1B & 0b11111000 | 0b00000001;
}

void loop()
{
  for (uint8_t selected = 0; selected < 5; selected++)
  {
    // OCR1A = 0x0;
    analogWrite(barLevelPin, 0);
    delay(1);
    selectPin(selected);
    analogWrite(barLevelPin, mappingValues[values[selected]]);
    // OCR1A = 128;

    // Serial.print(OCR1A);
    // Serial.print(" | ");
    // Serial.print(OCR1B);
    // Serial.print(" | ");
    // Serial.print(TCCR1A, BIN);
    // Serial.print(" | ");
    // Serial.println(TCCR1B, BIN); //format to binary

    delay(3);
  }
}

void selectPin(uint8_t input)
{
  for (uint8_t i = 0; i < 3; i++)
  {
    digitalWrite(selectorPins[i], input & 1);
    input >>= 1;
  }
  return;
}