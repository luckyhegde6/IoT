#ifdef SPARK
  #include "ThingSpeak/ThingSpeak.h"
#else
  #include "ThingSpeak.h"
#endif

#include <ESP8266WiFi.h>
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
#define ARDUINO_ARCH_ESP8266
#ifdef SPARK
    TCPClient client;
    // On Particle: 0 - 4095 maps to 0 - 3.3 volts
    #define VOLTAGE_MAX 3.3
    #define VOLTAGE_MAXCOUNTS 4095.0
#endif
Ticker ticker;
float t;
char auth[] = "55e4f2a287204fa69198463002d400c8";
// You should get Auth Token in the Blynk App.

#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);
unsigned long myChannelNumber = 259742;
const char * myWriteAPIKey = "RG6QS2WFY1YOFCP3";
Ticker flipper;

int count = 0;
void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}
// Task no.2: updating Thingspeak
void flip()
{     // set pin to the opposite state
  int sensorValue = t;
  Serial.println("Value Updated in Thingspeak \n");
  ThingSpeak.writeField(myChannelNumber, 1, sensorValue, myWriteAPIKey);
  ++count;
  // when the counter reaches a certain value, start blinking like crazy
  if (count == 20)
  {
    flipper.attach(0.1, flip);
    
  }
  // when the counter reaches yet another value, stop blinking
  else if (count == 120)
  {
    flipper.detach();
  }
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


    int status = WL_IDLE_STATUS;
    WiFiClient  client;
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#define ARDUINO_ARCH_ESP8266
  // On ESP8266:  0 - 1023 maps to 0 - 1 volts
  #define VOLTAGE_MAX 1.0
  #define VOLTAGE_MAXCOUNTS 1023.0

void setup() {
  Serial.begin(9600);
  // flip the pin every 15s
  flipper.attach(15, flip);
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

  WiFi.mode(WIFI_STA);

  int cnt = 0;
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

  Blynk.config(auth);

  ThingSpeak.begin(client);
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

void loop() {
  Blynk.run();
  delay(100);   // Wait a few seconds between measurements.
  t = analogRead(A0);   // Read temperature as Celsius

  if ( isnan(t)) {
    Serial.println("Failed to read from LDR sensor!");
    return;
  }

  Serial.print("Light: ");    // show in serial monitor
  Serial.print(t);
   Serial.print(" \t count: ");    // show in serial monitor
  Serial.print(count);
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
}

