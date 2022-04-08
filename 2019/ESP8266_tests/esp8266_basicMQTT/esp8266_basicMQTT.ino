/*
 Basic MQTT example modified for ESP8266 WiFi
 
  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
    Arduino IDE 1.6.4
    ESP8266 1.6.4-673-g8cd3697
    MQTT client library from
        https://github.com/knolleary/pubsubclient
    PROGMEM removed in PubSubClient.h and PubSubClient.cpp to avoid a 
    fatal compiler error.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "lucky";              //  your network SSID (name)
const char* pass = "laxmish53";       // your network password
byte server[] = { 192, 168, 0, 103 };       // MQTT broker

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
}

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void setup()
{
    Serial.begin(115200);

    // setting up Station AP
    WiFi.begin(ssid, pass);

    // Wait for connect to AP
    Serial.print("[Connecting]");
    Serial.print(ssid);
    int tries=0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        tries++;
        if (tries > 30) {
            Serial.println(F("fatal: Connect to AP failed"));
            while (1) continue;
            break;
        }
    }
    Serial.println();

    // print the SSID of the network you're attached to:
    Serial.print(F("SSID: "));
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print(F("IP Address: "));
    Serial.println(ip);

    // Connect to broker
    tries = 10;
    while (!client.connect("arduinoClient") && tries--) {
        Serial.print(F("mqtt connect failed "));
        Serial.println(tries, DEC);
        delay(500);
    }
    if (tries > 0) {
        Serial.println(F("arduinoClient connected"));
        client.publish("outTopic","hello world");
        client.subscribe("inTopic");
    }
    else {
        Serial.println(F("fatal: Connect to broker failed"));
        while (1) continue;
    }
}

void loop()
{
    client.loop();
}

