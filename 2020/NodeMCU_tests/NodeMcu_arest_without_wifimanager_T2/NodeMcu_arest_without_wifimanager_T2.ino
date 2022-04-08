#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

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
const int ledCount = 8;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;

MDNSResponder mdns;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "lucky";
//char pass[] = "laxmish53";
// Mac address should be different for each device in your LAN
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress device_ip  (192, 168,   0,  80);
IPAddress dns_ip     (  8,   8,   8,   8);
IPAddress gateway_ip (192, 168,   0,   1);
IPAddress subnet_mask(255, 255, 255,   0);

int R = 12;
int G = 13;
int B = 14;

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

// Create aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = "lucky";
const char* password = "laxmish53";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int Digital;
float Analog;

int RControl(String command);
int GControl(String command);
int BControl(String command);
int AControl(String command);


void setup(void) {
  // Start Serial
  //Serial.begin(115200);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

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
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.println(WiFi.localIP());
  //if you get here you have connected to the WiFi
  Serial.println("Wifi Connecting to:");
  Serial.println(ssid);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
  display.println("Wifi Connected:)");
  display.display();
  display.clearDisplay();
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  display.setTextSize(2);
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
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(52, 10);
  display.println("AP IP address:");
  display.println(myIP);
  display.display();
  display.clearDisplay();

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  // Set the title
  rest.title("aREST UI ESP8266_RGB_Test_1");

  // Create button to control pin
  rest.button(12);
  rest.button(13);
  rest.button(14);
  rest.button(16);

  // Init variables and expose them to REST API
  Digital = digitalRead(9);
  Analog = analogRead(A0);
  rest.variable("Digital", &Digital);
  rest.variable("Analog", &Analog);

  // Labels
  rest.label("Digital");
  rest.label("Analog");

  // Function to be exposed
  rest.function("R", RControl);
  rest.function("G", BControl);
  rest.function("B", GControl);
  rest.function("A", AControl);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("NodeMcu");

  // Connect to WiFi
  //  WiFi.begin(ssid, password);
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //  }
  //  Serial.println("");
  //  Serial.println("WiFi connected");
  //
  //  // Start the server
  //  server.begin();
  //  Serial.println("Server started");
  //
  //  // Print the IP address
  //  Serial.println(WiFi.localIP());
  // Start the server
  server.begin();
  Serial.println("Server started");

}

void loop() {

  Blynk.run(); //blynk run
  // Handle REST calls

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

}

int RControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(12, state);
  return 1;
}
int GControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(13, state);
  return 1;
}
int BControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(14, state);
  return 1;
}
int AControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(16, state);
  return 1;
}
void NeoOff()
{ for (j = 0; j < 8; j++) {
    pixels.setPixelColor(j, pixels.Color(0, 0, 0));
    pixels.show();
  }

}
void loop1() {
  pixels.setPixelColor(j, pixels.Color(0, 0, 0));
  pixels.show();
  for (j = 0; j < NUMPIXELS; j++) {

    // fade from green to red
    for (int i = 0; i < 255; i++) {
      pixels.setPixelColor(j, pixels.Color(i, 255 - i, 0));
      pixels.show();
      delay(DELAY);
    }

    // fade from red to blue
    for (int i = 0; i < 255; i++) {
      pixels.setPixelColor(j, pixels.Color(255 - i, 0, i));
      pixels.show();
      delay(DELAY);
    }

    // fade from blue to green
    for (int i = 0; i < 255; i++) {
      pixels.setPixelColor(j, pixels.Color(i, 0, 255 - i));
      pixels.show();
      delay(DELAY);
    }
    pixels.setPixelColor(j, pixels.Color(0, 0, 0));
    pixels.show();
  }

}
void loop2()
{
  for (j = NUMPIXELS; j > 0; j--) {

    // fade from green to red
    for (int i = 0; i < 255; i++) {
      pixels.setPixelColor(j, pixels.Color(i, 255 - i, 0));
      pixels.show();
      delay(DELAY);
    }

    // fade from red to blue
    for (int i = 0; i < 255; i++) {
      pixels.setPixelColor(j, pixels.Color(255 - i, 0, i));
      pixels.show();
      delay(DELAY);
    }

    // fade from blue to green
    for (int i = 0; i < 255; i++) {
      pixels.setPixelColor(j, pixels.Color(i, 0, 255 - i));
      pixels.show();
      delay(DELAY);
    }
  }
}
void loop3()
{
  for (int j = 0; j < NUMPIXELS; j++) {

    // fade from green to red
    for (int i = 255; i > 0; i--) {
      pixels.setPixelColor(j, pixels.Color(i, 255 - i, 0));
      pixels.show();
      delay(DELAY);
    }

    // fade from red to blue
    for (int i = 255; i > 0; i--) {
      pixels.setPixelColor(j, pixels.Color(255 - i, 0, i));
      pixels.show();
      delay(DELAY);
    }

    // fade from blue to green
    for (int i = 255; i > 0; i--) {
      pixels.setPixelColor(j, pixels.Color(i, 0, 255 - i));
      pixels.show();
      delay(DELAY);
    }

  }
}

