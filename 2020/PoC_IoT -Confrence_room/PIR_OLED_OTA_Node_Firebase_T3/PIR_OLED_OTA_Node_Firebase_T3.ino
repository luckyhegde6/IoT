#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <WiFiClientSecure.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "fireapp-4c89b.firebaseio.com"
#define FIREBASE_AUTH "1GEnrAqlI4oKoBI1yAE2VIgBJ0hCf75xH5CUGB3Y"
#define LIGHT 12
//for LED status
#include <Ticker.h>
Ticker ticker;
//for OLED display
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
/////Wifi Config
char ssid[] = "lucky";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
//const char* ssid = "lucky";
const char* password = "laxmish53";
#define led LED_BUILTIN
WiFiClientSecure client;
void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
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
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;       
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 10000; 
 
boolean lockLow = true;
boolean takeLowTime; 

// Variables for statechange will change:
int Counter = 0;   // counter for the number of state change
int State = 0;         // current state 
int lastState = 0;     // previous state
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;   
boolean EF = false;
 
int pirPin = 14;    //the digital pin connected to the PIR sensor's output       
int ledPin = 12;
 //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
boolean obj;
int objval;
 
/////////////////////////////
//SETUP
void setup(){
  Serial.begin (115200);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
 
  //give the sensor some time to calibrate
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("calibrating sensor ");
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
      display.println(" done");
      EF = false;
    display.println("SENSOR ACTIVE");
  display.display();
  delay(1000);
  display.clearDisplay();
  if(EF == false)
{
  Serial.println("Booting");
  Serial.print("Connecting Wifi: ");
  WiFi.mode(WIFI_STA);
  
  //set led pin as output
  pinMode(BUILTIN_LED, OUTPUT);
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
  Serial.println("Connected to Wifi :)");
  ticker.detach();
  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
 Serial.println("");
  Serial.println("WiFi connected");
 String my_ssid = WiFi.SSID(); 
 Serial.print("SSID: ");
  Serial.println(my_ssid);
  Serial.println("IP address: ");
  IPAddress my_ip = WiFi.localIP();
  Serial.println(my_ip);
display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("WiFi connected");
  display.print("SSID: ");
  display.println(my_ssid);
  display.println("IP address: ");
  display.println(my_ip);
  display.display();
  delay(500);
  display.clearDisplay();
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("PIR_Sensor Status", "To be updated");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
delay(1000);}
else
  {
     Serial.println("Kindly check Sensor ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Kindly check Sensor ");
  display.display();
  delay(500);
  display.clearDisplay();}
}
 
////////////////////////////
//LOOP
void loop(){
 ArduinoOTA.handle();
       if(EF == false)
  {
   ArduinoOTA.handle();
    delay(100);
    // clear the screen
  Motiondetect();
  delay(1000);}
  else
  {  Serial.println("Kindly check Sensor ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Kindly check Sensor ");
  display.display();
  delay(500);
  display.clearDisplay();}
  }
  
