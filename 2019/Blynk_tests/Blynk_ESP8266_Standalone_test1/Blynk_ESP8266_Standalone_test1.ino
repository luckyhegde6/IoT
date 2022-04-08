/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";


void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
pinMode(A0,INPUT);
pinMode(14,INPUT);
  Blynk.begin(auth, "lucky_home", "laxmish53");
}

void loop()
{ 
  int light = analogRead(A0);
  
  Blynk.run();
  WidgetLED led1(V0); //register to virtual pin 1
       led1.off();

       if (light>500)
{
  led1.on();
  for (int i=0;i<255;i++)
{analogWrite(13,i);
delay(10);}
}
delay(30000);
}       
  BLYNK_READ(V1) {// Widget in the app READs Virtal Pin V1 with the certain frequency
{int IRval = analogRead(14);
  // This command writes Arduino's uptime in seconds to Virtual Pin V5
 Blynk.virtualWrite(1,IRval);
 delay(30000);
}
  }
