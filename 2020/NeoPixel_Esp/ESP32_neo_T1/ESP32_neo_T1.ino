#include <WiFi.h>
#include <WiFiUdp.h>

#include <Adafruit_NeoPixel.h>
#define DELAY 5       // 20ms internal delay; increase for slower fades

#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 8;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0,1,2,3,4,5,6,7};   // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;


const char* ssid     = "lucky";
const char* password = "laxmish53";
WiFiServer server(80);

void setup()
{ pixels.begin(); // This initializes the NeoPixel library.
  
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode


  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();
  blinkStartConfig();

  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    blinkSmartConfig();
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("SmartConfig received.");

  //Wait for WiFi to connect to AP
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    delay(500);
  }

  Serial.println("WiFi Connected.");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
delay(10);
// We start by connecting to a WiFi network

//    Serial.println();
//    Serial.println();
//    Serial.print("Connecting to ");
//    Serial.println(ssid);
    //WiFi.begin(ssid, password);

  WiFi.mode(WIFI_AP_STA);  //need both to serve the webpage and take commands via tcp
  IPAddress ip(1,2,3,4);
  IPAddress gateway(1,2,3,1); 
  IPAddress subnet(255,255,255,0); 
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP("ESP32"); //Access point is open

  delay(1000);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
    server.begin();

}


int value = 0;
void blinkSmartConfig() {
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);              // wait for a second 
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
    delay(50);
}

void blinkClearConfig() {
  int i=0;
  while(i<=3) {
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);              // wait for a second 
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    i++;
  }
}

void blinkStartConfig() {
  pinMode(5,OUTPUT);
  int i=0;
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
}
void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<h1>ESP32 Neopixel Test1 </h1>");
            client.print("<button onclick='location.href=\"/H\"'> LED ON </button><br>");
            client.print("<button onclick='location.href=\"/L\"'> LED OFF </button><br>");
            client.print("<input type='range' min='0' max='255' value='0' step='5' onchange='document.getElementById('range2').innerHTML = value'/>");
            client.print("<span id='range2'>0</span><br>");
           // client.print("");
           client.print("<p>The localip is </p>");
           client.print(WiFi.localIP());
           
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(5, HIGH);               // GET /H turns the LED on
          loop1();
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);                // GET /L turns the LED off
          lightsof();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
