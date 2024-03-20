#include <LiquidCrystal_I2C.h>
#include "wattmeter.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
WattMeter wattmeter(A0, A1, 1500);

const uint16_t displayDuration = 30E3;     //  milliseconds
const uint16_t displayPageDuration = 5E3;  //  milliseconds

uint8_t displayPage = 0;
unsigned long lastDisplayEnable = 0;
unsigned long lastDisplayUpdate = 0;
bool enableDisplay = true;
float lastPower = 0;

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  wattmeter.update();
  switchDisplay();
  updateDisplay();
}

void switchDisplay() {
  float currentPower = wattmeter.getPower(false);
  float powerDifference = abs(currentPower - lastPower);
  lastPower = currentPower;

  if (powerDifference >= 1.25) {
    lastDisplayEnable = millis();
    lcd.backlight();
    enableDisplay = true;
  }

  if (enableDisplay) {
    unsigned long currentMillis = millis();
    unsigned long elapsedTime;

    if (currentMillis < lastDisplayEnable) {
      elapsedTime = (2^32 - 1 - lastDisplayEnable + currentMillis);
    } else {
      elapsedTime = currentMillis - lastDisplayEnable;
    }

    uint16_t displayDurationNow = displayDuration;

    if (currentPower == 0.0) {
      displayDurationNow = displayDuration / 3;
    }

    if (elapsedTime > displayDurationNow) {
      enableDisplay = false;
      lcd.clear();
      lcd.noBacklight();
    }
  }
}

void updateDisplay() {
  if (!enableDisplay) {
    return;
  }

  unsigned long currentMillis = millis();
  unsigned long elapsedTime;

  if (currentMillis < lastDisplayUpdate) {
    elapsedTime = (2^32 - 1 - lastDisplayUpdate + currentMillis);
  } else {
    elapsedTime = currentMillis - lastDisplayUpdate;
  }

  if (elapsedTime >= displayPageDuration) {
    displayPage++;
    lastDisplayUpdate = currentMillis;
  }

  if (displayPage >= 2) {
    displayPage = 0;
  }

  lcd.setCursor(0, 0);
  switch (displayPage) {
    case 0:
      lcd.print("Voltage: ");
      lcd.print(wattmeter.getVoltageRMS(false), 0);
      lcd.print(" V      ");
      lcd.setCursor(0, 1);
      lcd.print("Current: ");
      lcd.print(wattmeter.getCurrentRMS(false), 2);
      lcd.print(" A      ");
      break;
    case 1:
      lcd.print("Power: ");
      lcd.print(wattmeter.getPower(false), 0);
      lcd.print(" W      ");
      lcd.setCursor(0, 1);
      lcd.print("T: ");
      lcd.print(wattmeter.getCumulativePower(false), 6);
      lcd.print(" kWh      ");
      break;
  }
}
