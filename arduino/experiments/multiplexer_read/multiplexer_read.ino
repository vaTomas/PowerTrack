const uint8_t selectorPins[3] = {13, 12, 8};
const uint8_t analogPin = 18; //PIN_A4

void setup()
{
    Serial.begin(9600);
    pinMode(analogPin, INPUT);
    for (uint8_t pin : selectorPins)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void loop()
{
    for (uint8_t selected = 0; selected < 5; selected++)
    {
        selectPin(selected);
        Serial.print("Selected: ");
        Serial.print(selected);
        Serial.print(" | Value: ");
        Serial.println(analogRead(analogPin));
        delay(1000);
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
