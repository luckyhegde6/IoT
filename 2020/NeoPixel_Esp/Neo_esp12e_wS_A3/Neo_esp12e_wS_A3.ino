#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
#define DELAY 5       // 20ms internal delay; increase for slower fades
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 8;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0,1,2,3,4,5,6,7};   // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;


// Replace with your network credentials
const char* ssid = "lucky";
const char* password = "laxmish53";

ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = 13;
int gpio2_pin = 16;

void setup(void){
  
  pixels.begin(); // This initializes the NeoPixel library.
  
  Serial.begin(115200);
  webPage += "<h1>ESP8266 Web Server NeoPixel</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
//  webPage += "<input type='range' min='0' max='255' value='0' step='5' onchange='document.getElementById('range2').innerHTML = value'/> <span id='range2'>0</span>";
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  
  WiFi.begin(ssid, password);
 /* WiFi.mode(WIFI_AP_STA);  //need both to serve the webpage and take commands via tcp
  IPAddress ip(1,2,3,4);
  IPAddress gateway(1,2,3,1); 
  IPAddress subnet(255,255,255,0); 
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP("Lucky_neopixel"); //Access point is open
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("");*/

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
    digitalWrite(gpio0_pin, HIGH);
    loop3();
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    lightsof();
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    loop1();
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    loop2(); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 

