#include "ESP8266WiFi.h"//for wifi
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" 
SSD1306  display(0x3c, 4, 5);
typedef void (*Demo)(void);
int counter = 1;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
    // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void loop() {
  // clear the display
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");

  delay(100);
}
