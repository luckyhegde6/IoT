#include <UbidotsESP8266.h>
#include <SoftwareSerial.h> 

#define SSID "lucky"
#define PASS "laxmish53"

#define TOKEN "HFWXf0uQ4enY1qeos1EMlosANjQhMe"
#define ID "58fa66a07625420d811c41f5"

Ubidots client(TOKEN);

void setup() {
  Serial.begin(115200);
  client.wifiConnection(SSID,PASS);
  //client.setDataSourceName("LDR");
 // client.setDataSourceLabel("ldr_data");
}

void loop() {
  float value = analogRead(A0);
  client.add(ID,value);
  client.sendAll();
}
