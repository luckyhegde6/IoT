#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x38,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup()
{
lcd.init();                      // initialize the lcd 
lcd.setBacklight(HIGH);
lcd.home (); // go home

 lcd.print("LUCKY's I2C LCD");  
}

void loop()
{
  int n;
 // Backlight on/off every 3 seconds
 lcd.setCursor (0,1); // go to start of 2nd line
 lcd.print(n++,DEC);
 lcd.setBacklight(LOW);      // Backlight off
 delay(1000);
 lcd.setBacklight(HIGH);     // Backlight on
 delay(1000);
}
