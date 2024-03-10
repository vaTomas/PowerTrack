#include <Wire.h> 
#include <pcf8574.h>
#include <LiquidCrystal_I2C.h>
#include <MCP4725.h>



PCF8574 ex1(0x20);
LiquidCrystal_I2C lcd(0x27,20,4);
MCP4725 MCP(0x60);

// Example write whole PCF8574 register
// Address 0x20 - A2, A1, A0 shorted to GND
// pinMode is not needed

void setup()
{
  MCP.begin();
  
  // initialize the lcd 
  lcd.init();                     
  lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
}

void loop() {
	ex1.write(0b10101010);
  lcd.setCursor(0,1);
  lcd.print("10101010");
  MCP.setValue(0);

  delay(2000);

	ex1.write(0b01010101);
  lcd.setCursor(0,1);
  lcd.print("01010101");

  lcd.noDisplay();
  lcd.noBacklight();
  MCP.setValue(2457);

  delay(2000);

	ex1.write(0x0);
  lcd.setCursor(0,1);
  lcd.print("00000000");
  MCP.setValue(4095);

  lcd.display();
  lcd.backlight();

  delay(2000);
}