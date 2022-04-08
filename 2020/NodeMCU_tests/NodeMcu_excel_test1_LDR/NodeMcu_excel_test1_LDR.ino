//-----------------------------------------------
//This sketch is combined from Adafruit DHT sensor and tdicola
//for dht.h library
//Along with some  esp8266 NodeMCU specifics from teos009    
// https://learn.adafruit.com/dht/overview
// https://gist.github.com/teos0009/acad7d1e54b97f4b2a88
//other Authors Arduino and associated Google Script:
//Aditya Riska Putra
//Ahmed Reza Rafsanzani
//Ryan Eko Saputro
//See Also
//http://jarkomdityaz.appspot.com/
//
//ELINS UGM
//
//Modified for Hackster.io project to the ESP8266 from
//a Ethernet Sheild project
//by Stephen Borsay
//Since Arduino can't handle https, we need to use Pushingbox API
//(uses http)to run 
//the Google Script (uses https).
/*
 *1keBZ8GuBs5eiuVtuHEtzduG3CYKGzGREgYhUrJSmWsk

https://script.google.com/macros/s/AKfycbxOYJqSI0KRV1fbZGqARTEogEuWBXgU8BpjXnR9rlw5BvHD1hk/exec
 
DeviceID: v0EAB1F4EFE4455B


http://api.pushingbox.com/pushingbox?devid=v0EAB1F4EFE4455B
&LDRdata=33

https://script.google.com/macros/s/AKfycbxOYJqSI0KRV1fbZGqARTEogEuWBXgU8BpjXnR9rlw5BvHD1hk/exec
*/

#include "ESP8266WiFi.h"
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <BlynkSimpleEsp8266.h>
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "ESP8266WiFi.h"
//for LED status
#include <Ticker.h>


const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "v0EAB1F4EFE4455B"; //device ID from Pushingbox 
float t;
Ticker ticker;
char auth[] = "55e4f2a287204fa69198463002d400c8";
// You should get Auth Token in the Blynk App.
#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);
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
void setup()
{
  Serial.begin(115200);
  Serial.println("LDR test!");
  Serial.println("OLED test!");
  pinMode(16, OUTPUT);
  pinMode(16, LOW);
  // Initialize display
  display.begin();

  // set display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
  delay(2000);
  display.clearDisplay();

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
  Serial.println("connected...yeey :)");
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
  display.println("connected...yeey :)");
    display.display();
  display.clearDisplay();
  ticker.detach();
     delay(1000);
  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);
  Serial.println("local ip");
   Serial.println(WiFi.localIP());
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
   display.println("local ip: ");
  display.println(WiFi.localIP());
    display.display();
  display.clearDisplay();
   delay(5000);
   int cnt = 0;
   
  Blynk.config(auth);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (cnt++ >= 10) {
      WiFi.beginSmartConfig();
      while (1) {
        delay(1000);
        if (WiFi.smartConfigDone()) {
          Serial.println();
          Serial.println("SmartConfig: Success");
          display.println("SmartConfig: Success");
             delay(500);
          break;
        }
        Serial.print("|");
      }
    }
  }

  WiFi.printDiag(Serial);
  Serial.println("Credentials accepted! Connected to wifi\n ");
  Serial.println("");
}

void showTemp(float temp) {
  display.setTextSize(1);
  display.setCursor(3, 0);
  display.println("Light Intensity");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
  display.print(temp);
  display.println(" ");
  display.display();
  display.clearDisplay();
}
void loop()
{
  
  //Wait between measurements longer then normal to slow donwn
  //google sheet populate, as We dont want to exceed free service quota
  delay(10000); //10 seconds, (sampling rate vs. service call quota)
  Blynk.run();
  delay(100);   // Wait a few seconds between measurements.
  t = analogRead(A0);   // Read temperature as Celsius

  if ( isnan(t)) {
    Serial.println("Failed to read from LDR sensor!");
    return;
  }

  Serial.print("Light: ");    // show in serial monitor
  Serial.print(t);
  Serial.print(" * \n");
  showTemp(t);   // show temp
  if ( t < 420)
  {
    pinMode(16, HIGH);
    Serial.print("LED Blink \t");
    Blynk.virtualWrite(V0, HIGH);
    delay(200);
    pinMode(16, LOW);
    Blynk.virtualWrite(V0, LOW);
    delay(200);
  }
    
  WiFiClient client;  //Instantiate WiFi object

    //Start or API service using our WiFi Client through PushingBox
    if (client.connect(WEBSITE, 80))
      { 
         client.print("GET /pushingbox?devid=" + devid + "&LDRdata=" + (String)t);

      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: NodeMcU/1.0");
      client.println("Connection: close");
      client.println();
      Serial.println("Data uploaded \t");
      }
}
