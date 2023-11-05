#define ameterPin A5

uint16_t minCalibrationCurrent = 511;

uint32_t lastOutputTime = millis();
uint64_t currentSampleSums = 0;
uint16_t currentSampleCount = 0;

void setup(){
    Serial.begin(9600);
    pinMode(ameterPin, INPUT);
    Serial.println("Voltmeter Ready");
}



void loop(){
    uint16_t presentCurrent = analogRead(ameterPin);

    currentSampleSums += presentCurrent;
    currentSampleCount++;

    if (millis() - lastOutputTime >= 1000) {
        uint16_t average = currentSampleSums / currentSampleCount;
        Serial.println(average);
        lastOutputTime = millis();
        currentSampleSums = 0;
        currentSampleCount = 0;
    }

    // if (presentCurrent < minCalibrationCurrent && presentCurrent > 511){
    //     minCalibrationCurrent = presentCurrent;
    // }

    // uint16_t current = (presentCurrent - minCalibrationCurrent);
    delay(4);
}