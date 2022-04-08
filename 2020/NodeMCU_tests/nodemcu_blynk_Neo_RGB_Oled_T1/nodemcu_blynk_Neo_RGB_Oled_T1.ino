#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define DELAY 5       // 20ms internal delay; increase for slower fades
#define PIN 10
#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
#define NUMPIXELS      8
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 6;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0,1,2,3,4,5,6,7};   // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;
//for LED status
#include <Ticker.h>
Ticker ticker;

MDNSResponder mdns;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lucky";
char pass[] = "laxmish53";
// Mac address should be different for each device in your LAN
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress device_ip  (192, 168,   0,  80);
IPAddress dns_ip     (  8,   8,   8,   8);
IPAddress gateway_ip (192, 168,   0,   1);
IPAddress subnet_mask(255, 255, 255,   0);


ESP8266WebServer server(80);

String webPage = "";

int R = 12;
int G = 13;
int B = 14;
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
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

BLYNK_WRITE(V1)
{
  int shift = param.asInt();
  for (int i = 0; i < pixels.numPixels(); i++)
  {
    pixels.setPixelColor(i, Wheel(shift & 255));
    // OR: strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) & 255));
  }
  pixels.show();
}

void setup(void){
  Serial.begin(9600);
 // Setup WiFi network
  WiFi.config(device_ip, gateway_ip, subnet_mask);
  //WiFi.begin(ssid, pass);
 
  pixels.begin();
  pixels.show();
   // Initialize display
  display.begin();

  // set display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
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
  Serial.println("Wifi Connected:)");
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
  display.println("Wifi Connected:)");
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
  webPage += "<h1>ESP8266 Web Server RGB + Neopixel T1</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #3 <a href=\"socket3On\"><button>ON</button></a>&nbsp;<a href=\"socket3Off\"><button>OFF</button></a></p>";
  webPage += "<p>Neopixel loop1 <a href=\"NeoL1\"><button>NeoL1</button></a>&nbsp;<a href=\"NeoL2\"><button>NeoL2</button></a></p>";
  webPage += "<p>Neopixel loop3 <a href=\"NeoL3\"><button>NeoL3</button></a>&nbsp;<a href=\"NeoOff\"><button>NeoOFF</button></a></p>";
  
  // preparing GPIOs
  pinMode(R, OUTPUT);
  digitalWrite(R, LOW);
  pinMode(G, OUTPUT);
  digitalWrite(G, LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B, LOW);
  // Debug console
  
  
  
 Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Setup Blynk
  WiFi.mode(WIFI_AP_STA);  //need both to serve the webpage and take commands via tcp 
  WiFi.softAPConfig(device_ip, gateway_ip, subnet_mask);
  WiFi.softAP("ESP8266_Neo_RGB"); //Access point is open

  delay(1000);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
  display.println("AP IP address:");
  display.println(myIP);
    display.display();
  display.clearDisplay();
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(R, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(R, LOW);
    delay(500); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(G, HIGH);
    delay(500);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(G, LOW);
    delay(500); 
  });
  server.on("/socket3On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(B, HIGH);
    delay(500);
  });
  server.on("/socket3Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(B, LOW);
    delay(500); 
  });
   server.on("/NeoL1", [](){
    server.send(200, "text/html", webPage);
   loop1();
    delay(100);
  });
  server.on("/NroL2", [](){
    server.send(200, "text/html", webPage);
    loop2();
    delay(100); 
  });
   server.on("/NeoL3", [](){
    server.send(200, "text/html", webPage);
    loop3();
    delay(100);
  });
  server.on("/NeoOff", [](){
    server.send(200, "text/html", webPage);
    NeoOff();
    delay(100); 
  });
  server.begin();
  Serial.println("HTTP server started");
  
}
 
void loop(void){
  
  Blynk.run();
  server.handleClient();
  
} 

void NeoOff()
{for (j = 0; j < 8; j++) {
          pixels.setPixelColor(j, pixels.Color(0,0,0)); 
           pixels.show();
        }
  
  }
void loop1(){
  pixels.setPixelColor(j, pixels.Color(0,0,0)); 
      pixels.show(); 
for (j=0;j<NUMPIXELS;j++){
  
  // fade from green to red
  for(int i=0; i<255; i++) {
     pixels.setPixelColor(j, pixels.Color(i,255-i,0)); 
      pixels.show(); 
    delay(DELAY);
  }

  // fade from red to blue
  for(int i=0; i<255; i++) {
       pixels.setPixelColor(j, pixels.Color(255-i,0,i)); 
        pixels.show(); 
    delay(DELAY);
  }

  // fade from blue to green
  for(int i=0; i<255; i++) {
     pixels.setPixelColor(j, pixels.Color(i,0,255-i)); 
      pixels.show(); 
    delay(DELAY); 
  }
  pixels.setPixelColor(j, pixels.Color(0,0,0)); 
      pixels.show(); 
   }

}
void loop2()
{
for (j=NUMPIXELS;j>0;j--){
  
  // fade from green to red
  for(int i=0; i<255; i++) {
     pixels.setPixelColor(j, pixels.Color(i,255-i,0)); 
      pixels.show(); 
    delay(DELAY);
  }

  // fade from red to blue
  for(int i=0; i<255; i++) {
       pixels.setPixelColor(j, pixels.Color(255-i,0,i)); 
        pixels.show(); 
    delay(DELAY);
  }

  // fade from blue to green
  for(int i=0; i<255; i++) {
     pixels.setPixelColor(j, pixels.Color(i,0,255-i)); 
      pixels.show(); 
    delay(DELAY); 
  }
 }
}
void loop3()
{
for (int j=0;j<NUMPIXELS;j++){
  
  // fade from green to red
  for(int i=255; i>0; i--) {
     pixels.setPixelColor(j, pixels.Color(i,255-i,0)); 
      pixels.show(); 
    delay(DELAY);
  }

  // fade from red to blue
  for(int i=255; i>0; i--) {
       pixels.setPixelColor(j, pixels.Color(255-i,0,i)); 
        pixels.show(); 
    delay(DELAY);
  }

  // fade from blue to green
  for(int i=255; i>0; i--) {
     pixels.setPixelColor(j, pixels.Color(i,0,255-i)); 
      pixels.show(); 
    delay(DELAY); 
  }

   }
 }

