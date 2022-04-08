#include <Wire.h>
#include "WiFi.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
      Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
  // Clear the buffer.
   display.clearDisplay();
  testscrolltext();
  // Clear the buffer.
  display.clearDisplay();
  printScanData("WiFi Scan Initiated");
  display.display();
}
 void testscrolltext(void) {
  display.clearDisplay(); // clear the display screen of the OLED
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Welcome");
  delay(2000);
  display.clearDisplay(); 
  display.println("Scanning Wifi");
  display.println("Iron Man");
  display.display();      
  delay(100);
}
 void printScanData(String wifidata) {
  display.clearDisplay(); // clear the display screen of the OLED
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Scanning");
  delay(2000);
  display.clearDisplay(); 
  display.println(wifidata);
  display.display();      
  delay(100);
}
void loop() {
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
      // Clear the buffer.
  display.clearDisplay();
  printScanData("scan done");
  display.display();
    if (n == 0) {
        Serial.println("no networks found");
              // Clear the buffer.
  display.clearDisplay();
  printScanData("no networks found");
  display.display();
    } else {
        Serial.print(n);
        Serial.println(" networks found");
                      // Clear the buffer.
  display.clearDisplay();
  printScanData("networks found");
  display.display();
  delay(100);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
                          // Clear the buffer.
  display.clearDisplay();
  printScanData(i + 1 + ": " +WiFi.SSID(i) +" (" +WiFi.RSSI(i)+")");
  display.display();
  delay(100);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(20000);
}
