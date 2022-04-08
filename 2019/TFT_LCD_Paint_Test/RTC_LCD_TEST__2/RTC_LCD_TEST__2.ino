// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
LiquidCrystal_I2C lcd(0x38,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
lcd.init();  
  Serial.begin(9600);  // Used to type in characters
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.noBacklight(); // finish with backlight on  
//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("HI! U r in I2c mode");
  delay(8000);  
// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Use Serial Mon");
  lcd.setCursor(0,1);
  lcd.print("Type to display");  
  delay(3000); // wait for console opening
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop ()
{  DateTime now = rtc.now();
   if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
     lcd.write(Serial.print(now.year(), DEC));
     lcd.write(Serial.print('/'));
     lcd.write( Serial.print(now.month(), DEC));
     lcd.write( Serial.print('/'));
     lcd.write(Serial.print(now.day(), DEC));
     lcd.write(Serial.print(" ("));
     lcd.write(Serial.print(daysOfTheWeek[now.dayOfTheWeek()]));
     lcd.write(Serial.print(") "));
     lcd.write(Serial.print(now.hour(), DEC));
     lcd.write(Serial.print(':'));
     lcd.write(Serial.print(now.minute(), DEC));
     lcd.write(Serial.print(':'));
     lcd.write(Serial.print(now.second(), DEC));
     lcd.write(Serial.println()); 
      }
}
/*void callrtc(){
DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
     // when characters arrive over the serial port...
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
        lcd.write(Serial.read());
      }
    } */
}
