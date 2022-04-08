#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);
const char* ssid = "lucky";
const char* password = "laxmish53";
int button = 16;            //GPIO 16
int LED = LED_BUILTIN;              // Builtin LED of ESP8266-12E board
const char* host = "maker.ifttt.com";     //IFTTT channel address
int buttonState = LOW;
int value = 1;
int flag = 0;
void setup()   {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(button, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // By default Off state
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  int sensorValue = analogRead(A0);
  if (sensorValue > 500)
  {
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
    if (value == 1) {
      WiFi.disconnect();
      Serial.println("Button Pressed");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("Button Pressed:");
      display.display();
      delay(100);
      WiFi.mode(WIFI_AP);
      WiFi.begin(ssid, password); // connecting to wifi
      if (flag == 1) {
        //Init WiFi as Station, start SmartConfig
        WiFi.mode(WIFI_AP_STA);
        WiFi.beginSmartConfig();
        //Wait for SmartConfig packet from mobile
        Serial.println("Waiting for SmartConfig.");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Waiting for SmartConfig.");
        display.display();
        delay(500);
        display.clearDisplay();
        while (!WiFi.smartConfigDone()) {
          delay(500);
          Serial.print(".");
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 10);
          display.println(".");
          display.display();
          delay(100);
        }
        display.clearDisplay();
        Serial.println("");
        Serial.println("SmartConfig received.");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("SmartConfig received.");
        display.display();
        delay(100);
        display.clearDisplay();
        Serial.println("Waiting for WiFi");
        //Wait for WiFi to connect to AP
        delay(500);
        Serial.print(".");
        Serial.println("WiFi Connected.");

        flag = 0;
      }
       if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Conencting");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Conencting..");
        display.display();
        delay(1000);
        display.clearDisplay();
        flag = 1;
      }
   if(WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Connected.");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("WiFi Connected...");
      display.display();
      delay(500);
      display.clearDisplay();
      flag = 0;
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("IP Address:.");
      display.println(WiFi.localIP());
      display.display();
      delay(2000);
      display.clearDisplay();
      digitalWrite(LED, LOW); // LED turns On
   }

      WiFiClient client;
      const int httpPort = 80;
      if (!client.connect(host, httpPort)) {
        Serial.println("Weak Network");
        return;
      }
      // We now create a URI for the request
      String url = "https://maker.ifttt.com/trigger/button_pressed/with/key/kdBNr-fiqACjPzsU7wLwx8eM52HNo7rXUxEEJDEaVD5";   //our link to trigger the event with special key and event name

      // This will send the request to the server
      client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  // GET request

      value = 0;
      delay(5000);
      digitalWrite(LED, HIGH); // LED turns Off
    }
    else {
    value = 1;
    delay(500);}
  }
  else {
    digitalWrite(LED, HIGH);    // turn the LED off by making the voltage LOW// print out the value you read:
  Serial.println(sensorValue);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.println("Sensor:");
  display.println(sensorValue);
  display.display();
  delay(100);

    // Clear the buffer.
    display.clearDisplay();
  }
}
