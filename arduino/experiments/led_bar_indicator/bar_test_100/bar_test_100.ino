#include <MCP4725.h> //DAC

MCP4725 MCP(0x60); //DAC at Address 0x60


float DACValues[5];
const long updateInterval = 2000; // update interval in milliseconds (2000ms = 2 seconds)
unsigned long lastUpdateTime = 0; 

uint16_t test;



void setup()
{
  DDRD |= 0b00011100; //Pins 3-5 to Output
}

void loop()
{
  updateDACValues();
  for(uint8_t i = 0; i<5; i++){
    Serial.println(DACValues[i]);
    MCP.setValue(0);
    selectSocket(i);
    MCP.setPercentage(DACValues[i]);
  }
}


void selectSocket(uint8_t socketNumber) {
  const uint8_t changeOnly = 0b00011100;
  PORTD &= ~0b00011100;
  PORTD |= (socketNumber << 2) & changeOnly;
}



void updateDACValues() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= updateInterval) {
    for (int i = 0; i < 5; i++) {
      DACValues[i] = random(100); // generate a random float between 0 and 100
    }
    lastUpdateTime = currentTime; // update the last update time
  }
}