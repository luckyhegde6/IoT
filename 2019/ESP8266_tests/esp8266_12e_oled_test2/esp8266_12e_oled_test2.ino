// Example sketch for testing OLED display

// We need to include Wire.h for I2C communication
#include <Wire.h>
#include "OLED.h"

// Declare OLED display
// display(SDA, SCL);
// SDA and SCL are the GPIO pins of ESP8266 that are connected to respective pins of display.
OLED display(4, 5);

void setup() {
  Serial.begin(9600);
  Serial.println("OLED test!");

  // Initialize display
  display.begin();

  // Test message
  display.print("Hello World");
  delay(3*1000);

  // Test display clear
  display.clear();
  delay(3*1000);

  // Test display OFF
  display.off();
  delay(3*1000);

  // Test display ON
  display.on();
  delay(3*1000);
}



void loop() {
  display.clear();
  // Test message
  display.print("Its Beast V2.0");
  delay(10*1000);
}
