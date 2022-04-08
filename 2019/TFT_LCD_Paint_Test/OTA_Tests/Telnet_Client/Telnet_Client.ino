#include <ESP8266WiFi.h>

// start telnet server (do NOT put in setup())
const uint16_t aport = 23; // standard port
WiFiServer TelnetServer(aport);
WiFiClient TelnetClient;

void setup() {
  TelnetServer.begin();
  TelnetServer.setNoDelay(true);
} // setup()
//  on another computer start your Telnet client with connect to NodeMCU
//  example: telnet 192.168.4.1

void loop() {
  // send info to Telnet
  if (!TelnetClient) {  // otherwise it works only once
        TelnetClient = TelnetServer.available();
  if (TelnetClient.connected()) {
    TelnetClient.println("Telnet Test");
  }
} 
