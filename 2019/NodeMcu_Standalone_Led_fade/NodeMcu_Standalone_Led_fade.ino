#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";

int ledPin2=2; // assign widget LED to tie with gpio pin 2
WidgetLED led2(V2);
int prev = HIGH;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lucky_home";
char pass[] = "laxmish53";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    // Wait until connected
  }
}

// V2 LED Widget is fading
void fadeLedWidget()
{
  static int value = 0;
  static int delta = 30;
  value += delta;
  if (value > 255 || value < 0) {
    delta = -delta;
  } else {
    Serial.print("LED on V2: ");
    Serial.println(value);
    led2.setValue(value);
  }
}

void loop()
{
  Blynk.run();
  int led2value = digitalRead(ledPin2);
  Serial.print("LED on V2: ");
  Serial.println(led2value);
  if (led2value != prev){  
    Blynk.virtualWrite (ledPin2,led2value);}  
      prev = led2value;
      BLYNK_WRITE(V2); //Button Widget is writing to pin V2
{
  int pinData = led2value; 
}
    
}

