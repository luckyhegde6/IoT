#include <Wire.h>
#include <RealTimeClockDS1307.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define Display_Clock_Every_N_Seconds 10 
#define Display_ShortHelp_Every_N_Seconds 60
String tz;
int hours = 0;
int minutes = 0;
int seconds = 0;
int dates = 0;
int months = 0;
int years = 0;
int ap = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2); 
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
}

void loop() {
  RTC.readClock();
    if(ap == 1)
    {
    tz = "PM";
    }
    else
    {
    tz ="AM";
    }
    lcd.home();
    hours = RTC.getHours();
    minutes = RTC.getMinutes();
    seconds = RTC.getSeconds();
    ap = RTC.isPM();
    dates = RTC.getDate();
    months = RTC.getMonth();
    years = RTC.getYear();
    lcd.print(hours);
    lcd.print(":");
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds);
    lcd.print(" ");
    lcd.print(tz);
    lcd.setCursor(0, 1);
    lcd.print(dates);
    lcd.print(":");
    lcd.print(months);
    lcd.print(":");
    lcd.print(years);
    delay(250);
    lcd.clear();
    lcd.home();
    lcd.print(hours);
    lcd.print(" ");
    lcd.print(minutes);
    lcd.print(" ");
    lcd.print(seconds);
    lcd.print(" ");
    lcd.print(tz);
    lcd.setCursor(0, 1);
    lcd.print(dates);
    lcd.print(" ");
    lcd.print(months);
    lcd.print(" ");
    lcd.print(years);
    delay(250);
    lcd.clear();
}
/*//RTC.start(); -- starting the RTC
//integers for holding the various time values.
int hours = 0;
int minutes = 0;
int seconds = 0;
int dates = 0;
int months = 0;
int years = 0;
int date = 0;
//syntax for setting the values to the integers
RTC.readClock();   //This line is essential for the other commands to work.
//Commands for getting the individual time values.
hours = RTC.getHours();
minutes = RTC.getMinutes();
seconds = RTC.getSeconds();
dates = RTC.getDate();
months = RTC.getMonth();
years = RTC.getYear();
date = RTC.getDayofWeek();
//finally just print the stored data (refer next step)
//RTC.stop(); -- stopping RTC

//extra code for finding out whether its AM or PM when the clock is in 12h mode.
//declare an integer and string.
/*
int AP = 0;
String TZ;
//then read the data from the module.
ampm = RTC.isPM();
//use an if loop to find out whether its AM or PM.
if(ampm == 1)
{
    am = "PM";
}
else
{
    am ="AM";
}
*/
/*
RTC.setHours(4);
RTC.setMinutes(35);
RTC.setSeconds(14);
RTC.setDate(9);
RTC.setMonth(6);
RTC.setYear(14);
RTC.set24h();
//RTC.setAM();
RTC.setPM();
RTC.setDayofWeek(1);<br>
*/
/*//These commands deal with the settings in the module.
//Checks whether the clock is running.
RTC.isStopped();
//Check whether it is AM or PM depending on the output(given above).
RTC.isPM();
//Checks whether the clock is in 24hour mode.
RTC.is12hour();
//Toggles between the 12hour mode and 24hour mode.
RTC.switchTo24h();
*/
