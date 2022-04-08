#include <ESP8266WiFi.h>  
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#define OLED_RESET LED_BUILTIN

const char* ssid = "lucky";
const char* password = "laxmish53";
int button = 16;            //GPIO 16
int LED = LED_BUILTIN;              // Builtin LED of ESP8266-12E board
const char* host = "maker.ifttt.com";     //IFTTT channel address
int buttonState = LOW;
int value = 1;
int RED_LED=12;
int GREEN_LED=13;
int BLUE_LED=14;
int sensorValue;
int DL_check;
const int sleepTimeS = 10;
Adafruit_SSD1306 display(OLED_RESET);
//for LED status
#include <Ticker.h>
Ticker ticker;


void tick()
{
  //toggle state
  int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}
void setup(){  
  Serial.begin(115200);
// initialize digital pin LED_BUILTIN as an output.
Serial.println("ESP8266 in normal mode");
  pinMode(LED_BUILTIN, OUTPUT);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  //set led pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
   pinMode(GREEN_LED, HIGH);
  pinMode(BLUE_LED, HIGH);
  // start ticker with 0.5 because we start in AP mode and try to connect
  ticker.attach(0.6, tick);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
    display.setTextSize(21);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Wifi Connected");
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
  ticker.detach();
  //keep LED on
  digitalWrite(LED_BUILTIN, LOW);
  
}

void loop() {
sensorValue = analogRead(A0);
  DL_check = digitalRead(16);
  if(DL_check==1)
  {
    pinMode(GREEN_LED, HIGH);
    delay(500);
      pinMode(BLUE_LED, LOW);
    live();
    DL_check = digitalRead(16);
  display.clearDisplay();
    }
  else
  {
    pinMode(GREEN_LED, LOW);
  pinMode(BLUE_LED, HIGH);
   
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Sensor Testing:");
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
  display.println("Sensor:");
  display.println(sensorValue);
  display.display();
    delay(100);
  display.clearDisplay();
  }
  
}
void live()
{
sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Sensor:");
  display.println(sensorValue);
  display.display();
    delay(100);
    // Clear the buffer.
  display.clearDisplay();
    while(sensorValue>500)
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
      Serial.println("Sensor Value High");
      defconn();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("IFTTT ON");
      display.display();
      delay(1000);
        display.clearDisplay();
    WiFiClient client;
      const int httpPort = 80;
      if (!client.connect(host, httpPort)) {
        Serial.println("Weak Network");
        return;
      }
      // We now create a URI for the request
      String url = "https://maker.ifttt.com/trigger/motion_detect/with/key/kdBNr-fiqACjPzsU7wLwx8eM52HNo7rXUxEEJDEaVD5";   //our link to trigger the event with special key and event name

      // This will send the request to the server
      client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  // GET request
        Serial.println();
Serial.println("closing connection");
display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("IFTTT triggered");
        display.println();
         display.println("closing connection");
        display.display();
        delay(1000);
        display.clearDisplay();
  // Sleep
  Serial.println("ESP8266 in sleep mode");
  display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
   display.println("ESP8266 in sleep mode");
        display.display();
        delay(1000);
        display.clearDisplay();
        digitalWrite(LED_BUILTIN, HIGH); // LED turns Off
    ESP.deepSleep(sleepTimeS * 1000);
    ESP.restart();
      
 }
    }
    
void defconn()
{
     Serial.println(WiFi.status());
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("WiFi status ");
      display.println(WiFi.status());
      display.display();
      delay(500);
      display.clearDisplay();
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
      display.println("IP Address:");
      display.println(WiFi.localIP());
      display.display();
      delay(2000);
      display.clearDisplay();
      }
      else{
   WiFi.mode(WIFI_AP);
       WiFi.begin(ssid, password); // connecting to wifi
       }
}
