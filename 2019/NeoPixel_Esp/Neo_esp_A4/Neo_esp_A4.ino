#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
MDNSResponder mdns;

#define DELAY 5       // 20ms internal delay; increase for slower fades
#define PIN            12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 6;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0,1,2,3,4,5,6,7};   // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;
// Replace with your network credentials
const char* ssid = "lucky";
const char* password = "laxmish53";

ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = LED_BUILTIN;
int gpio2_pin = 16;

void setup(void){
  
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
    loop1(); 
  });
  server.begin();
  Serial.println("HTTP server started");
  pixels.begin(); // This initializes the NeoPixel library.
}
 
void loop(void){
  server.handleClient();
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
