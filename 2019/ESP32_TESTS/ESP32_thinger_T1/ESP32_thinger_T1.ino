#include <WiFi.h>
#include <ThingerESP32.h>

#define USERNAME "ESP32"
#define DEVICE_ID "ESP32"
#define DEVICE_CREDENTIAL "luckyhegde"

#define SSID "lucky"
#define SSID_PASSWORD "laxmish53"

// define your board pin here
#define LED_PIN 16

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_PIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
