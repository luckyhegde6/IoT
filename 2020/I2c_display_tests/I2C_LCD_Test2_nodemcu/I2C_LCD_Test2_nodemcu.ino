/*
14CORE NodeMCU i2C 16x2 LCD SCREEN
Test COde.........................
*/
 
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
LiquidCrystal_I2C lcd(0x38, 16, 2);
 
void setup()
{
  lcd.init();   // initializing the LCD
  lcd.noBacklight(); // Enable or Turn On the backlight 
  lcd.setCursor(0, 1);
  lcd.print("16x2 LCD TEST"); // Start Print text to Line 1
  lcd.setCursor(0, 2);      
  lcd.print("-----------------------"); // Start Print Test to Line 2
}
 
void loop()
{
  // Nothing Absolutely Nothing!
}
