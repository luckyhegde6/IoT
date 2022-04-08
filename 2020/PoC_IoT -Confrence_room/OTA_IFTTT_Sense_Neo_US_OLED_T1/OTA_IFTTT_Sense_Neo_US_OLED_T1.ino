#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>//ota library
//for wifi manager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>   //for Neopixel
#include <IFTTTMaker.h>         //IFTTT maker
//for OLED display
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);
//for LED status
#include <Ticker.h>
Ticker ticker;
///Neo pixel settings
#define PIN 15
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 30; // delay for half a second
///wifi settings
char ssid[] = "lucky";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
//const char* ssid = "lucky";
const char* password = "laxmish53";
#define KEY "h4VW6l_BSVEIKMFMwtvhuBCD9QX7qtE40RnqTOwTyKk"  // Get it from this page https://ifttt.com/services/maker/settings
#define EVENT_NAME "Nodemcu" // Name of your event name, set when you are creating the applet
#define EVENT_NAME2 "Activity_detect" // Name of your event name, set when you are creating the applet
///Ultrasonic sensor pins
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
//////

int button = 2;            //GPIO 2
int buttonState = LOW;
int DL_check;
const int sleepTimeS = 10;
///////


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
}void setrange()
{
  for(int r=0;r<20;r++)
    {
     Range = analogRead(RangePin);
     Range = map(Range, 0, 1024, 0, 200);
  // in case the sensor value is outside the range seen during calibration
  Range = constrain(Range, 0, 200);
  Serial.println("Range is:");
  Serial.println(Range);
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255-Range,Range,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).
    }
  delay(1000);
     }
     
    if ((Range>0) && (Range<50))
    {Range = 60;}
}
void setup() {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  Serial.begin (115200);
  pixels.begin(); // This initializes the NeoPixel library.
    pixels.show();
    pixels.setBrightness(50);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  
// initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
   
  ////set the Range:
  Serial.println("Set the range for Motion detect");
  setrange();
  Serial.println("Range Set is:");
  Serial.println(Range);
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
    
    // Attach an interrupt to the ISR vector
/*attachInterrupt(0, pin_ISR, CHANGE);
    void pin_ISR() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
}*/
Serial.println("Booting");
  Serial.print("Connecting Wifi: ");
  WiFi.mode(WIFI_STA);
  /*WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart()
     // scan for existing networks:
  Serial.println("Scanning available networks...");
  scanNetworks();

  // attempt to connect using WEP encryption:
  Serial.println("Attempting to connect to your network...");
  status = WiFi.begin(ssid);

  Serial.print("SSID: ");
  Serial.println(ssid);
  }
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
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

  //triggerEvent takes an Event Name and then you can optional pass in up to 3 extra Strings
  if(ifttt.triggerEvent(EVENT_NAME, my_ssid, my_ip.toString())){
    Serial.println("Successfully Connected");
  } else
  {
    Serial.println("Failed!");
  }
  ifttt.triggerEvent(EVENT_NAME2,"Monitoring started", "0 Sec");
}

void loop() {
   ArduinoOTA.handle();
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  delay(500);
   // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    display.clearDisplay();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
      display.print(Serial.read());
    }
  }
       DL_check = digitalRead(2);
  if(DL_check==1)
  {
pixels.setPixelColor(0,255,0,0);
    delay(100);
  for(int i=0;i<NUMPIXELS;i++){
  pixels.setPixelColor(i,0,150,0);
    pixels.show();
  }
    Slive();
    DL_check = digitalRead(2);
  display.clearDisplay();
    }
  else
  {
   
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Sensor Testing:");
  display.display();
    delay(100);
  display.clearDisplay();
  Sensorcheck();
  DL_check = digitalRead(2);
  }
  // Clear the buffer.
  display.clearDisplay();
  
}



