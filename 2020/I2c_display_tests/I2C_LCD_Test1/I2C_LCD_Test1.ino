#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x38,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{

   lcd.init();    // initialize the lcd
  
  lcd.noBacklight(); //turns off LCD BACKlight
  delay(1000);
  lcd.backlight();
    delay(1000);
  lcd.noBacklight(); //turns off LCD BACKlight
  lcd.clear();
  
  lcd.setCursor(2,1);
  // Print a message to the LCD.
  lcd.print(" Hello, world! ");

}


void loop()
{
}
