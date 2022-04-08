#include "ESP8266WiFi.h"//for wifi
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" 
#include "images.h"
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

void drawFontFaceDemo() {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hi");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "This is Lucky");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Test OLED");
}


void drawProgressBarDemo() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}
void drawImageDemo() {
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

void loop() {
  // clear the display
  display.clear();
  

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
drawImageDemo();
  delay(200);
  drawProgressBarDemo();
  delay(200);
  counter++;
  drawFontFaceDemo();
  delay(200);
}

