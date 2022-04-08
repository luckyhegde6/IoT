#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//For Wifi manager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>  //Neopixel
#include <IFTTTMaker.h>         //IFTTT maker
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
//Neopixel config
#define PIN 15
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 30; // delay for half a second
/////Wifi Config
char ssid[] = "lucky";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
//const char* ssid = "lucky";
const char* password = "laxmish53";
#define KEY "h4VW6l_BSVEIKMFMwtvhuBCD9QX7qtE40RnqTOwTyKk"  // Get it from this page https://ifttt.com/services/maker/settings
#define EVENT_NAME "Nodemcu" // Name of your event name, set when you are creating the applet
#define EVENT_NAME2 "Activity_detect" // Name of your event name, set when you are creating the applet
////for Ultrasonic pins
#define trigPin 12
#define echoPin 13
#define led LED_BUILTIN

//////////Range & motion detect variables//////////////
int RangePin = A0;
int Range = 0;
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
boolean obj;
int objval;

int calibrationTime = 10;       
 long duration, distance;
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 5000; 
 
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
///////
void setrange()
{
  for(int r=0;r<20;r++)
    {
     Range = analogRead(RangePin);
     Range = map(Range, 0, 1024, 0, 200);
  // in case the sensor value is outside the range seen during calibration
  Range = constrain(Range, 0, 200);
  Serial.println("Range is:");
  Serial.println(Range);
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Range is:");
  display.println(Range);
  display.display();
  display.clearDisplay();
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255-Range,Range,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).
    }
  delay(1000);
  display.clearDisplay();
     }
     
    if ((Range>0) && (Range<50))
    {Range = 60;}
}

WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);
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

void setup() {
  Serial.begin (115200);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  // This initializes the NeoPixel library.
  pixels.setBrightness(50);
   pixels.begin(); 
    pixels.show();
    
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
// initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
 
  ////set the Range:
  Serial.println("Set the range for Motion detect");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Set the range for Motion detect");
  display.display();
  delay(500);
  display.clearDisplay();
  setrange();
  Serial.println("Range Set is:");
  Serial.println(Range);
    // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Range Set is:");
  display.println(Range);
  display.display();
  delay(500);
  display.clearDisplay();
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if(distance >0 && distance <= Range)
{
   Serial.print("distance: ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println(" ");
    digitalWrite (led, HIGH);
delay(500);
digitalWrite (led, LOW);
Serial.println(" done");
Serial.println("SENSOR ACTIVE");
delay(500);
EF = false;}
      else{
    Serial.println("SENSOR not ACTIVE");
    delay(1000);
    EF = true;}
    }
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("calibrating sensor ");
  display.println(" done");
    display.println("SENSOR ACTIVE");
  display.display();
  delay(1000);
  display.clearDisplay();
    // Attach an interrupt to the ISR vector
/*attachInterrupt(0, pin_ISR, CHANGE);
    void pin_ISR() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
}*/
if(EF == false)
{
Serial.println("Booting");
  Serial.print("Connecting Wifi: ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Booting");
  display.print("Connecting Wifi: ");
  display.display();
  delay(500);
  display.clearDisplay();
  WiFi.mode(WIFI_STA);
  /*   // scan for existing networks:
  Serial.println("Scanning available networks...");
  scanNetworks();
  WiFi.disconnect();
  delay(100);*/
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
  //triggerEvent takes an Event Name and then you can optional pass in up to 3 extra Strings
  if(ifttt.triggerEvent(EVENT_NAME, my_ssid, my_ip.toString())){
    Serial.println("Successfully Connected");
  } else
  {
    Serial.println("Failed!");
  }
  ifttt.triggerEvent(EVENT_NAME2,"Connected to: " + String(my_ssid), my_ip.toString());
  ifttt.triggerEvent(EVENT_NAME2,"Monitoring started", "0 Sec");}
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

void loop() {
  if(EF == false)
  {
   ArduinoOTA.handle();
    delay(100);
    // clear the screen
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Motiondetect();
  ReadState();
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



