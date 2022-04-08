/*
 *  Timer1 library example
 *  June 2008 | jesse dot tane at gmail dot com
 */

#include "TimerOne.h"

void setup()
{
  pinMode(12, OUTPUT);
  Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.pwm(13, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}

void callback()
{
  digitalWrite(12, digitalRead(12) ^ 1);
}

void loop()
{
  // your program here...
}
//attachInterrupt(function, period)
