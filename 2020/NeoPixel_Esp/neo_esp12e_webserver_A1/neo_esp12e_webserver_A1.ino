#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const int RELAY_PIN = 14; //RELAY
#define LED_BUILTIN 0
 
const char* ssid = "Lucky_home";
const char* password = "laxmish53";
MDNSResponder mdns;
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void){
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(RELAY_PIN, 1);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED_BUILTIN, 0);
 
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
 
  server.on("/", handleRoot);
 
  server.on("/a", [](){
  server.send(200, "text/plain", "Okay -- Light is ON!");
  digitalWrite(RELAY_PIN, 1);
  digitalWrite(LED_BUILTIN, 1);
  });
 
  server.on("/b", [](){
  server.send(200, "text/plain", "Okay -- Light is OFF!");
  digitalWrite(RELAY_PIN, 0);
  digitalWrite(LED_BUILTIN, 0);
  });

  server.onNotFound(handleNotFound);
 
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
}
