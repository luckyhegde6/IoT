#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//needed for library
#include <DNSServer.h>
#include <WiFiManager.h>   
//for LED status
#include <Ticker.h>
Ticker ticker;
Ticker flipper;

int count = 0;

void flip()
{
  int state = digitalRead(1);  // get the current state of GPIO1 pin
  digitalWrite(1, !state);     // set pin to the opposite state
  
  ++count;
  // when the counter reaches a certain value, start blinking like crazy
  if (count == 20)
  {
    flipper.attach(0.1, flip);
  }
  // when the counter reaches yet another value, stop blinking
  else if (count == 120)
  {
    flipper.detach();
  }
}

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
extern "C" {
  #include "user_interface.h"
}

#include "data.h"
#include "NameList.h"
#include "APScan.h"
#include "ClientScan.h"
#include "Attack.h"

const static char *ssid = "pwned";
const static char *password = "deauther"; //must have at least 8 characters

ESP8266WebServer server(80);

/*
I had some troubles implementing singleton classes.
see: https://github.com/esp8266/Arduino/issues/500
They fixed this issue within a newer SDK version - the one we can't use, so I used global variables.
*/

NameList nameList;

APScan apScan;
ClientScan clientScan;
Attack attack;

void sniffer(uint8_t *buf, uint16_t len){
  clientScan.packetSniffer(buf,len);
}

void startWifi(){
  WiFi.mode(WIFI_STA);
  wifi_set_promiscuous_rx_cb(sniffer);
  WiFi.softAP(ssid, password); //for an open network without a password change to:  WiFi.softAP(ssid);
  String _ssid = (String)ssid;
  String _password = (String)password;
  Serial.println("SSID: "+_ssid);
  Serial.println("Password: "+_password);
  if(_password.length()<8) Serial.println("WARNING: password must have at least 8 characters!");
  if(_ssid.length()<1 || _ssid.length()>32) Serial.println("WARNING: SSID length must be between 1 and 32 characters!");
}



void setup(){

  Serial.begin(115200);
  delay(2000);
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
  Serial.println("connected...yeey :)");
  ticker.detach();
  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);

  nameList.begin();
  //nameList.clear();
  nameList.load();

  Serial.println("");
  Serial.println("starting...");

  startWifi();
  attack.generate(-1);

  /* ========== Web Server ========== */

  /* HTML sites */
  server.onNotFound(load404);

  server.on("/", loadIndex);
  server.on("/index.html", loadIndex);
  server.on("/clients.html", loadClients);
  server.on("/attack.html", loadAttack);
  server.on("/functions.js", loadFunctionsJS);

  /* header links */
  server.on ("/style.css", loadStyle);

  /* JSON */
  server.on("/APScanResults.json", sendAPResults);
  server.on("/APScan.json", startAPScan);
  server.on("/APSelect.json", selectAP);
  server.on("/ClientScan.json", startClientScan);
  server.on("/ClientScanResults.json", sendClientResults);
  server.on("/clientSelect.json", selectClient);
  server.on("/setName.json", setClientName);
  server.on("/attackInfo.json", sendAttackInfo);
  server.on("/attackStart.json", startAttack);
pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  // flip the pin every 0.3s
  flipper.attach(0.3, flip);
  server.begin();
}

void loop(){
  if(clientScan.sniffing){
    if(clientScan.stop()){
      startWifi();
    }
  } else{
    server.handleClient();
    attack.run();
  }
}

void load404(){ server.send ( 200, "text/html", data_get404()); }
void loadIndex(){ server.send ( 200, "text/html", data_getIndexHTML() ); }
void loadClients(){ server.send ( 200, "text/html", data_getClientsHTML()); }
void loadAttack(){ server.send ( 200, "text/html", data_getAttackHTML() ); }
void loadFunctionsJS(){ server.send( 200, "text/javascript", data_getFunctionsJS() ); }
void loadStyle(){ server.send ( 200, "text/css", data_getStyle() ); }

//==========AP-Scan==========
void startAPScan(){ 
  if(apScan.start()){
    server.send ( 200, "text/json", "true");
    attack.stopAll();
  }
}

void sendAPResults(){ server.send ( 200, "text/json", apScan.getResults()); }

void selectAP(){
  if(server.hasArg("num")) {
    apScan.select(server.arg("num").toInt());
    server.send ( 200, "text/json", "true");
    attack.stopAll();
  }
}

//==========Client-Scan==========
void startClientScan(){
  if(server.hasArg("time") && apScan.selected > -1 && !clientScan.sniffing) {
    server.send(200, "text/json", "true");
    clientScan.start(server.arg("time").toInt());
    attack.stop(0);
  } else server.send ( 200, "text/json", "Error: no selected access point");
}

void sendClientResults(){ server.send( 200, "text/json", clientScan.getResults()); }

void selectClient(){
  if(server.hasArg("num")) {
    clientScan.select(server.arg("num").toInt());
    attack.stop(0);
    server.send ( 200, "text/json", "true");
  }
}

void setClientName(){
  if(server.hasArg("id") && server.hasArg("name")) {
    nameList.add(clientScan.getClientMac(server.arg("id").toInt()),server.arg("name"));
    server.send ( 200, "text/json", "true");
  }
}

//==========Attack==========
void sendAttackInfo(){ server.send ( 200, "text/json", attack.getResults()); }

void startAttack(){
  if(server.hasArg("num")) {
    int _attackNum = server.arg("num").toInt();
    if(apScan.selected > -1 || _attackNum == 3){
      attack.start(server.arg("num").toInt());
      server.send ( 200, "text/json", "true");
      digitalWrite(BUILTIN_LED, LOW);
      delay(10);
      digitalWrite(BUILTIN_LED, HIGH);
    }
  }
}
