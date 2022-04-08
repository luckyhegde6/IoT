#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "ESP8266WiFi.h"
//#include "SSD1306.h"

#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);
//SSD1306  display(0x3c, 4, 5);
 
void setup() {
  Serial.begin(9600); 
  Serial.println("LDR test!");
    Serial.println("OLED test!");

  // Initialize display
  display.begin();


  
  // set display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
  delay(2000);
  display.clearDisplay();
  
}

void showTemp(float temp) {
  display.setTextSize(1);
  display.setCursor(3,0);
  display.println("Light Intensity");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(52,10);
  display.print(temp);
  display.println(" ");
  display.display();
  display.clearDisplay();}
void loop() {

  delay(1000);   // Wait a few seconds between measurements.
  float t = analogRead(A0);   // Read temperature as Celsius
 
  if ( isnan(t)) {
    Serial.println("Failed to read from LDR sensor!");
    return;
  }
 
  Serial.print("Light: ");    // show in serial monitor
  Serial.print(t);
  Serial.print(" * \n");
  showTemp(t);   // show temp
}
