/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
#include <Wire.h>
#include "OLED.h"
// Declare OLED display
// display(SDA, SCL);
// SDA and SCL are the GPIO pins of ESP8266 that are connected to respective pins of display.
OLED display(4, 5);
void setup() {
  Serial.begin(115200);

  // Initialize display
  display.begin();
   // Test display clear
  display.clear();
  delay(3*1000);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
  display.print("Setup done");
}

void loop() {
  Serial.println("scan start");
  display.print("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  display.print("scan done");
  if (n == 0)
   { Serial.println("no networks found");
    display.print("no networks found");}
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    display.print(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      display.print(" (");
     Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      display.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*"); 
      delay(10);
    }
  }
  Serial.println("");
  display.print("");

  // Wait a bit before scanning again
  delay(5000);
}
