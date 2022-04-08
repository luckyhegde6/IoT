#define BLYNK_DEBUG // Optional, this enables lots of prints
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "55e4f2a287204fa69198463002d400c8";

int ledPin2=2; // assign widget LED to tie with gpio pin 2
WidgetLED led(V2);
int led2value = digitalRead(ledPin2);
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lucky_home";
char pass[] = "laxmish53";
SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, blinkLedWidget);
}

// V2 LED Widget is blinking
void blinkLedWidget()
{
  if (led2value == 0) {
    led.off();
  //  Blynk.virtualWrite(V2, LOW);
    Serial.println("LED on V2: off");
  } else {
    led.on();
   //  Blynk.virtualWrite(V2, HIGH);
    Serial.println("LED on V2: on");
  }
}

void loop()
{
  Blynk.run();
   timer.run();
  Serial.print("LED on V2: ");
  Serial.println(led2value);
  Blynk.syncVirtual(V2);
  BLYNK_LOG("This is my value: %d", 10);
  delay(1000);
  
} /* 
BLYNK_CONNECTED()
  {
  if (isFirstConnect) {
    Blynk.syncVirtual(V2);
    //Blynk.syncAll();
  }
  BLYNK_READ(V5) // Widget in the app READs Virtal Pin V5 with the certain frequency
{
  // This command writes Arduino's uptime in seconds to Virtual Pin V5
  Blynk.virtualWrite(5, millis() / 1000);
}
  }BLYNK_WRITE(V1) // Widget WRITEs to Virtual Pin V1
{   
  int x = param[0].asInt(); // getting first value
  int y = param[1].asInt(); // getting second value
  int z = param[N].asInt(); // getting N value
}*/


 /*   if (led2value == 1 ){  
    Blynk.virtualWrite(V2, HIGH);}
  else
   {  
    Blynk.virtualWrite(V2, LOW);}
BLYNK_WRITE(V2); //Button Widget is writing to pin V2
{
  int pinData = led2value; 
}*/
    

/*
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
}*/
/*
 *   while (Blynk.connect() == false) {
    // Wait until connected
  }
  // Make pin 2 default HIGH, and attach INT to our handler
pinMode(2, INPUT_PULLUP);
}
int prevState = -1;
int currState = -1;
long lastChangeTime = 0;

 * void checkPin()
{
  // Invert state, since button is "Active LOW"
  int state = !digitalRead(2);
  // Debounce mechanism
  long t = millis();
  if (state != prevState) {
    lastChangeTime = t;
  }
  if (t - lastChangeTime > 50) {
    if (state != currState) {
      currState = state;
      Blynk.virtualWrite(V2, state);
    }
  }
  prevState = state;
}
 */


