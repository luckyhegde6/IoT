#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
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
void setup() {
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
void Wifi_SConfig(){ int cnt = 0;  

  // set for STA mode
  WiFi.mode(WIFI_STA);
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  // led status at pin16
  pinMode(LED_BUILTIN,OUTPUT);
  
  //configure pin0 
  pinMode(16, INPUT_PULLUP);

  // deplay for 2 sec for smartConfig
  Serial.println("2 sec before clear SmartConfig");
  delay(2000);
  
  // read pullup
  int isSmartConfig = digitalRead(16);
  if (isSmartConfig==0) {
    // bink for clear config
    blinkClearConfig();
    Serial.println("clear config");
    // reset default config
    WiFi.disconnect();

  }

  // if wifi cannot connect start smartconfig
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(cnt++ >= 15){
       WiFi.beginSmartConfig();
       while(1){
           delay(500);
           if(WiFi.smartConfigDone()){
             Serial.println("SmartConfig Success");
             blinkSmartConfig();
             break;
           }
       }
    }
  }

  Serial.println("");
  Serial.println("");
  
  WiFi.printDiag(Serial);

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void blinkSmartConfig() {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(50);              // wait for a second 
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    delay(50);
}

void blinkClearConfig() {
  int i=0;
  while(i<=3) {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(100);              // wait for a second 
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    delay(100);
    i++;
  }
}

void blinkStartConfig() {
  pinMode(LED_BUILTIN,OUTPUT);
  int i=0;
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
}


void loop() {
    WiFi.disconnect();
  int sensorValue = analogRead(A0);
  if (sensorValue > 500)
  {
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
    if (value == 1) {
      Serial.println("Sensor Value High");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("IFTTT ON");
      display.display();
      delay(1000);
        display.clearDisplay();
      WiFi.mode(WIFI_AP);
       WiFi.begin(ssid, password); // connecting to wifi
      Serial.println(WiFi.status());
      if(WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Connected.");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("WiFi Connected...");
      display.display();
      delay(500);
      display.clearDisplay();
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
      if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Conencting");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Smart config ON..");
        display.display();
        delay(1000);
        display.clearDisplay();
        Wifi_SConfig();
      }
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
display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("IFTTT triggered");
        display.display();
        delay(1000);
        display.clearDisplay();
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
 WiFi.disconnect();
    // Clear the buffer.
    display.clearDisplay();
  }
      
      
}
