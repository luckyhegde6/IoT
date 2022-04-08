#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <MQTTClient.h>
int status = WL_IDLE_STATUS;
MQTTClient client;
WiFiSSLClient net;
int buttonPin = 2;
boolean buttonState = false;
boolean oldButtonState = false;
boolean lightStatus=false;
const char* ssid  = "lucky_home";     //  your network SSID (name)
const char* password = "laxmish53";  // your network password
const char* userName = "luckyhegde";
const char* deviceName = "button";
const char* deviceId = "038987a4-414c-4645-b09d-e754a354ba66";
const char* devicePsw = "940208d5-0efa-4ea7-918b-b793e4c7d7e6";
void setup() {
 Serial.begin(9600);
 WiFi.begin(ssid, password);
 client.begin("mqtt.arduino.cc", 8883, net);
 connect();
 pinMode(2, INPUT);
}
void connect() {
 Serial.print("checking wifi...");
 while ( status != WL_CONNECTED) {
   Serial.print("Attempting to connect to WPA SSID: ");
   Serial.println(ssid);
   // Connect to WPA/WPA2 network:
   status = WiFi.begin(ssid, password);
   // wait 10 seconds for connection:
   delay(4000);
 }
 Serial.println("connecting...");
 while (!client.connect(deviceName, deviceId, devicePsw)) {
   Serial.print(".");
 }
 Serial.println("connected!");
}
void loop() {
 client.loop();
 buttonState = digitalRead(buttonPin);
 if (!buttonState && oldButtonState) {
   lightStatus = !lightStatus;
   if (lightStatus) {
     client.publish("/<username>/button/status", "on");
     Serial.println("publishing on");
   } else {
     client.publish("/<username>/button/status", "off");
     Serial.println("publishing off");
   }
 }
 oldButtonState = buttonState;
 delay(50);
}
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
 Serial.print("incoming: ");
 Serial.print(topic);
 Serial.print(" - ");
 Serial.print(payload);
 Serial.println();
}
