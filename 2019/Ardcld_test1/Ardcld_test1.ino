#include <WiFi101.h>
#include <ArduinoCloud.h>

/////// Wifi Settings ///////
char ssid[] = "lucky_home";
char pass[] = "laxmish53";


// Arduino Cloud settings and credentials
const char userName[]   = "luckyhegde";
const char thingName[] = "IoTLED";
const char thingId[]   = "667bc08b-d580-4703-a475-08657d7e001d";
const char thingPsw[]  = "a5bf4bba-2120-4347-a519-73f53953ff63";


WiFiSSLClient sslClient;


// build a new object "IoTLED"
ArduinoCloudThing IoTLED;


void setup() {
  Serial.begin (9600);

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // unsuccessful, retry in 4 seconds
    Serial.print("failed ... ");
    delay(4000);
    Serial.print("retrying ... ");
  }


  IoTLED.begin(thingName, userName, thingId, thingPsw, sslClient);
  IoTLED.enableDebug();
  // define the properties
  IoTLED.addProperty("cloudLedStatus", INT, R, TIMED, 60);
  
}

void loop() {
  IoTLED.poll();

  IoTLED.writeProperty("cloudLedStatus", "oh...");
  
  delay(1000);
  IoTLED.writeProperty("cloudLedStatus", "yeah!");
  
  delay(1000);
}

