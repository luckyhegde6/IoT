#include <Wire.h>
#include <Wire.h>
#include "OLED.h"
// Declare OLED display
// display(SDA, SCL);
// SDA and SCL are the GPIO pins of ESP8266 that are connected to respective pins of display.
OLED display(4, 5);

void setup()
{
  Wire.begin();
 // Initialize display
  display.begin();
   // Test display clear
  display.clear();
  delay(3*1000);
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");
  display.print("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      display.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
        display.print("0");
      Serial.print(address,HEX);
      
      Serial.println("  !");
      display.print("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      display.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
        display.print("0");
      Serial.println(address,HEX);
      
    }    
  }
  if (nDevices == 0)
    {Serial.println("No I2C devices found\n");
    display.print("No I2C devices found\n");}
  else
    {Serial.println("done\n");
    display.print("done\n");}

  delay(5000);           // wait 5 seconds for next scan
}
