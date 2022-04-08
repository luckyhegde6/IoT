#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" 
#include "ESP8266WiFi.h"
// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 4, 5);
int counter = 1;

void setup() {
 Serial.begin(115200);
  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
 // Set WiFi to station mode and disconnect from an AP if it was previously connected
 WiFi.mode(WIFI_STA);
 WiFi.disconnect();
 delay(100);

 Serial.println("Setup done");
 display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, "Setup done");
}

void loop() {
  // clear the display
  display.clear();
 Serial.println("scan start");
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, "scan start");
drawProgressB();
 // WiFi.scanNetworks will return the number of networks found
 int n = WiFi.scanNetworks();
 Serial.println("scan done");
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(0, 20, "scan done");
 if (n == 0){
  display.clear();
 Serial.println("no networks found");
 display.drawString(0, 10, "no networks found");}
 else
 {
 Serial.print(n);
 display.clear();
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(0, 5, String(n));
 Serial.println(" networks found ");
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(10, 5, " networks found");
 for (int i = 0; i < n; ++i)
 {
 // Print SSID and RSSI for each network found
 Serial.print(i + 1);
 Serial.print(": ");
 Serial.print(WiFi.SSID(i));
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
  display.drawString(5, 10, String(WiFi.SSID(i)));
 Serial.print(" (");
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(20, 20, " (");
 Serial.print(WiFi.RSSI(i));
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(25, 20, String(WiFi.RSSI(i)));
 Serial.print(")");
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(30, 10,")");
 Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
 display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
 display.drawString(35, 10, String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*"));
 delay(10);
 }
 }
 Serial.println("");

/*if (Serial.available())  {
    
                display.clear();
                inChar = Serial.read();
                string+=inChar;               
                display.setCursor(0,0); 
                display.print(string);               
                display.display();             
              
        
    }  */
      display.display();
 // Wait a bit before scanning again
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
  counter++;
 delay(100);
}


  void drawProgressB() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}
  
