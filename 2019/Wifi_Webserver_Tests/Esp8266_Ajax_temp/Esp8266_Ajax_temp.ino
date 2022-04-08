#include <ESP8266WiFi.h>
#include “indexl.h”                                                             //This file contains the HTML code

const char* ssid = “SSID”;
const char* password = “PASSWORD”;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

int dac = 0;                                                                                      //The initial value of pin 5
int DigitalPin[] = {4, 12, 13};                      //the array holding the digital pins so that we can reference them easily using for loops
int DacPin = 5;

void setup() {
Serial.begin(115200);
delay(10);
pinMode(4,INPUT);
pinMode(4, INPUT_PULLUP);                     //Using Input Pullup for the digital input to work
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);

// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print(“Connecting to “);
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(“.”);
}
Serial.println(“”);
Serial.println(“WiFi connected”);

// Start the server
server.begin();
Serial.println(“Server started”);

// Print the IP address
Serial.println(WiFi.localIP());
}

void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
return;
}

// Wait until the client sends some data
Serial.println(“new client”);
while(!client.available()){
delay(1);
}

// Read the first line of the request
String command1 = client.readStringUntil(‘/’); //This stores the irrelevant portion of the URL
String command = client.readStringUntil(‘/’); //This will parse the rest of the URL into valid inputs

if (command == “digital”) {                                                            //for example /digital/12/1
int pin, value;
pin = client.parseInt();                                                                     //for /digital/12/1, pin=12
Serial.println(pin);
if (client.read() == ‘/’) {
value = client.parseInt();                                                              //for /digital/12/1, value=1
digitalWrite(pin, value);                                                         //lights LED connected to Pin 12
}
else {
value = digitalRead(pin);
}
client.print(F(“digital,”));
client.print(pin);
client.print(F(“,”));
client.println(value);                                                               //sends digital,12,1 to web page
}
else if (command == “dac”){                                                             //for example /dac/5/190
int pin, value;
pin = client.parseInt();                                                                           //for /dac/5/190, pin=5
if (client.read() == ‘/’) {
value = client.parseInt();                                                               //for /dac/5/190, value=190
dac = value;                                       //dac is used as a placeholder for storing slider value
analogWrite(pin, value);                                                        //lights led on pin 5 using PWM
}
else {
value = dac;
}
client.print(F(“dac,”));
client.print(pin);
client.print(F(“,”));
client.println(value);                                                                //sends dac,5,190 to web page
}
else if (command == “status”) {                                                         //for example /status/99
int pin, value;
client.print(F(“status”));                                            //the string of data will start with “status”
for (int thisPin = 0; thisPin < 3; thisPin++) {                              //which means pins 4,12,13
pin = DigitalPin[thisPin];                                                          //for thispin=0, DigitalPin[0]=4
value = digitalRead(pin);                                                                //status of pin4 i.e. 0 or 1
client.print(F(“#”));
client.print(pin);
client.print(F(“=”));
client.print(value);
}
{
pin = DacPin;
value = dac;
client.print(F(“#”));
client.print(pin);
client.print(F(“=”));
client.print(value);
}
{
value = analogRead(A0);
float lux=value;
client.print(F(“#A0”));
client.print(F(“=”));
client.print(lux);
}                          //after for loop, the string will be status#4=0#12=0#13=1#5=0#A0=756.00
client.println(“”);
}
else {
String s = “HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n”; //Send web page if request is empty i.e. the initial request
s += file1;
client.flush();
// Send the response to the client in bursts of 2000
while(s.length()>2000)
{
String dummy = s.substring(0,2000);
client.print(dummy);
s.replace(dummy,” “);
}

client.print(s);
delay(1);
Serial.println(“Client disconnected”);

// The client will actually be disconnected
// when the function returns and ‘client’ object is destroyed
}
}
