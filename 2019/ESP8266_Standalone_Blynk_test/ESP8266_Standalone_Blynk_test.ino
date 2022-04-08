/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "78de7a0ff1194b599ac0bc9e4527bd58";

void setup()
{
  Serial.begin(1152// Import required libraries
#include "ESP8266WiFi.h"
int ledPin = 2; //On the ESP-12, the onboard LED is connected to pin 2
 
// WiFi parameters
const char* ssid = "<redacted>";
const char* password = "<redacted>";
 
void setup(void)
{ 
// Start Serial
Serial.begin(115200);
 
// Connect to WiFi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
// Print the IP address
Serial.println(WiFi.localIP());
 
pinMode(ledPin, OUTPUT);       // Initialize the BUILTIN_LED pin as an output
}
 
void loop() {
  digitalWrite(ledPin, LOW);   // Turn the LED on (Note that LOW is the voltage level
                               // but actually the LED is on; this is because 
                               // it is acive low on the ESP-01)
  delay(1000);                 // Wait for a second
  digitalWrite(ledPin, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                 // Wait for two seconds (to demonstrate the active low LED)
}00);
  Blynk.begin(auth, "lucky_home", "laxmish53");
}

void loop()
{
  Blynk.run();
}

