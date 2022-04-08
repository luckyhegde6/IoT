#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
WidgetLED led2(V2);

SimpleTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "lucky_home", "laxmish53");
    while (Blynk.connect() == false) {
    // Wait until connected
  }

  timer.setInterval(300L, fadeLedWidget);
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
  timer.run();
}


