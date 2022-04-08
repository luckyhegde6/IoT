//#define BLYNK_DEBUG // Optional, this enables lots of prints
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";

const int ledPin2=2; // assign widget LED to tie with gpio pin 2

WidgetLED led(V2);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lucky_home";
char pass[] = "laxmish53";
SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  //timer.setInterval(1000L, blinkLedWidget);
}

//This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1

// V2 LED Widget is blinking
/*void blinkLedWidget()
{
  if (led.getValue()) {
    led.off();
  //  Blynk.virtualWrite(V2,LOW);
    Serial.println("LED on V2: off");
  } else {
    led.on();
   //  Blynk.virtualWrite(V2,HIGH);
    Serial.println("LED on V2: on");
  }
}
*/
void loop()
{
  Blynk.run();
 //  timer.run();
 int led2value = digitalRead(ledPin2);
  Serial.print("LED on V2: ");
  Serial.println(led2value);
  if (led2value == 0) {
    Blynk.virtualWrite(V2,LOW);
    Serial.println("LED on V2: off");
    } else {
     Blynk.virtualWrite(V2,HIGH);
    Serial.println("LED on V2: on");
  }
  
 // BLYNK_LOG("This is my value: %d", 10);
  
}
/*BLYNK_READ(V2)
{
  if (led2value ==0) {
    Blynk.virtualWrite(V2,LOW);
    Serial.println("LED on V2: off");
  } else {
     Blynk.virtualWrite(V2,HIGH);
    Serial.println("LED on V2: on");
  }
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
}
*/
