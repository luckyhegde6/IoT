#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define DELAY 5       // 20ms internal delay; increase for slower fades

#define PIN 12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 6;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0,1,2,3,4,5,6,7};   // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;

const int RELAY_PIN = 16; //RELAY
//#define LED_BUILTIN 1
 
const char* ssid = "lucky";
const char* password = "laxmish53";
MDNSResponder mdns;
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from Luckyhegde! its Neopixel web server");
  for (j = 0; j < 8; j++) {
          pixels.setPixelColor(j, pixels.Color(255,255,255)); 
           pixels.show();
}
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void){
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(RELAY_PIN, 1);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED_BUILTIN, 0);
 
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
 
  server.on("/", handleRoot);
 
  server.on("/a", [](){
  server.send(200, "text/plain", "Okay -- neo ON! Loop1");
  digitalWrite(RELAY_PIN, 1);
  digitalWrite(LED_BUILTIN, 1);
  loop1();
  });
 
  server.on("/b", [](){
  server.send(200, "text/plain", "Okay -- Neo On! Loop2");
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED_BUILTIN, 0);
  loop2();
  });
    server.on("/c", [](){
  server.send(200, "text/plain", "Okay -- Neo On! Loop3");
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);
  digitalWrite(LED_BUILTIN, 1);
  loop3();
  });
    server.on("/d", [](){
  server.send(200, "text/plain", "Okay -- Neo On! Loop4");
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED_BUILTIN, 1);
   delay(500);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);
  digitalWrite(LED_BUILTIN, 1);
  loop4();
  });

  server.onNotFound(handleNotFound);
 
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
}
