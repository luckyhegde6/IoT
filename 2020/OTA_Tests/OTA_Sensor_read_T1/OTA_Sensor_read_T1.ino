#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

int sensor = 12;
const uint16_t aport = 8266;
WiFiServer TelnetServer(aport);
WiFiClient Telnet;

const char* ssid = "lucky";
const char* password = "laxmish53";

void setup() {
  pinMode(sensor, INPUT);
 // pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  //Port defaults to 8266
  ArduinoOTA.setPort(8266);

 // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("myesp8266");

 // No authentication by default
 ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  int Sensorvalue = analogRead(sensor);
  Serial.println("Sensor Value:");
  Serial.println(Sensorvalue);
  delay(100);
  
/*  if (sensorvalue ==)
  {
    digitalWrite(14, HIGH);
    delay(100);
    digitalWrite(14, LOW);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    )*/
   // printDebug();
}

void printDebug(const char* c){
//Prints to telnet if connected
  Serial.println(c);
 
  if (Telnet && Telnet.connected()){
    Telnet.println(c);
  }
}
