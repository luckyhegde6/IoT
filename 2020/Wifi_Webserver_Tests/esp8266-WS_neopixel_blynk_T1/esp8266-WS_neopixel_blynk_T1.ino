#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

//for LED status
#include <Ticker.h>
Ticker ticker;

MDNSResponder mdns;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "66d8c9388a5a4e4b809ef045540047f";

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

int R = 0;
int G = 2;
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
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

BLYNK_WRITE(V1)
{
  int shift = param.asInt();
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, Wheel(shift & 255));
    // OR: strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) & 255));
  }
  strip.show();
}

void setup(void){
 

  strip.begin();
  strip.show();
  Serial.begin(115200);
  
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
  Serial.println("WiFi connected:)");
  ticker.detach();
  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);
  
  webPage += "<h1>ESP8266 Web Server RGB + Neopixel T1</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #3 <a href=\"socket3On\"><button>ON</button></a>&nbsp;<a href=\"socket3Off\"><button>OFF</button></a></p>";
  
  
  // preparing GPIOs
  pinMode(R, OUTPUT);
  digitalWrite(R, LOW);
  pinMode(G, OUTPUT);
  digitalWrite(G, LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B, LOW);
  // Debug console
  Serial.begin(9600);

  // Setup WiFi network
  WiFi.config(device_ip, gateway_ip, subnet_mask);
  //WiFi.begin(ssid, pass);
  
 Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Setup Blynk
  Blynk.config(auth);
  WiFi.mode(WIFI_AP_STA);  //need both to serve the webpage and take commands via tcp 
  WiFi.softAPConfig(device_ip, gateway_ip, subnet_mask);
  WiFi.softAP("ESP8266_Neo_RGB"); //Access point is open

  delay(1000);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
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
    delay(1000); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(G, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(G, LOW);
    delay(1000); 
  });
  server.on("/socket3On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(B, HIGH);
    delay(1000);
  });
  server.on("/socket3Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(B, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
  
}
 
void loop(void){
  
  Blynk.run();
  server.handleClient();
  
} 
