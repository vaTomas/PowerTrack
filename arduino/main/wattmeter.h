#include <Arduino.h>

class WattMeter {
private:
  float power;
  float currentRMS;
  float voltageRMS;

  uint8_t voltmeterPin;
  uint8_t ammeterPin;

  unsigned long previousMillis = millis();
  float cumulativePower;

  uint16_t samples;


public:
  // Constructor
  WattMeter(uint8_t voltmeterPin, uint8_t ammeterPin, uint16_t samples) : voltmeterPin(voltmeterPin), ammeterPin(ammeterPin), samples(samples) {}

  // Public methods
  float getVoltageRMS(bool rescan = true) {
    if (rescan) {
      this->read();
    }
    return this->voltageRMS;
  }

  float getCurrentRMS(bool rescan = true) {
    if (rescan) {
      this->read();
    }
    return this->currentRMS;
  }

  float getPower(bool rescan = true) {
    if (rescan) {
      this->read();
    }
    return this->power;
  }

  float getCumulativePower(bool rescan = true) {
    if (rescan) {
      this->read();
    }
    return this->cumulativePower/3.6E6;
  }

  void update(){
    read();
  }

private:
  // Private method to read voltage and current RMS values
  void read() {
    const float peakVoltage = 600 * sqrt(2); 
    const float peakCurrent = 20; 
    const float reciprocalSamples = 1.0f / static_cast<float>(samples);
    float totalVoltage = 0;
    float totalCurrent = 0;


    for (int i = 0; i < samples; i++) {
      float sampleVoltage = (analogRead(voltmeterPin) / 1023.0) * (2 * peakVoltage) - peakVoltage;
      float sampleCurrent = (analogRead(ammeterPin)-102.3)/(920.7-102.3) * (2 * peakCurrent) - peakCurrent;
      totalVoltage += sampleVoltage * sampleVoltage;
      totalCurrent += sampleCurrent * sampleCurrent;
    }

    this->voltageRMS = sqrt(totalVoltage * reciprocalSamples);
    this->currentRMS = sqrt(totalCurrent * reciprocalSamples) - 0.0225;

    // Calculate power assuming resistive load (P = Vrms * Irms)
    

    // If voltage is too low, consider it as 0
    if (this->voltageRMS <= 5.0) {
      this->voltageRMS = 0.0;
    }

    if (this->currentRMS <= 0.05) {
      this->currentRMS = 0.0;
    }
    this->power = this->voltageRMS * this->currentRMS;
    updateCumulativePower();
  }


  void updateCumulativePower() {
    unsigned long currentMillis = millis();


    // Calculate time elapsed since last update
    unsigned long elapsedTime;
    if(currentMillis < previousMillis){
      elapsedTime = (2^32-1-previousMillis+currentMillis);
    }
    else{
      elapsedTime = currentMillis - previousMillis;
    }
    // Update previousMillis
    previousMillis = currentMillis;

    // Calculate energy consumption (in watt-seconds) since last update
    float energy = power * (elapsedTime / 1000.0); // Convert milliseconds to seconds

    // Add energy to cumulative power
    this->cumulativePower += energy;
  }
};
