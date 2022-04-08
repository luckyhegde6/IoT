#include <Wire.h>
void setup() {
Serial.begin (115200);
Serial.println ("Scanning I2C device...");
Wire.begin();
int count =0;
for (byte i = 0; i <50; i++)
{
Wire.beginTransmission (i);
if (Wire.endTransmission () == 0)
{
Serial.print ("Address found->");
Serial.print (" (0x");
Serial.print (i, HEX);
Serial.println (")");
count++;
}
Serial.print ("Found ");
Serial.print (count, DEC);
Serial.println (" device");
}
}
void loop() {}
