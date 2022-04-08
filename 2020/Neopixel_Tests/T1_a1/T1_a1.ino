#include <Adafruit_NeoPixel.h>
#define DELAY 5       // 20ms internal delay; increase for slower fades
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 6;    // the number of LEDs in the bar graph
int range;
int ledPins[] = {0,1,2,3,4,5,6,7};   // an array of pin numbers to which LEDs are attached
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int j;
void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
    Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For
    // example 'a' = 97, 'b' = 98, and so forth:

    switch (inByte) {
      case 'a':
        loop1();
        break;
      case 'b':
        loop2();
        break;
      case 'c':
       loop3();
        break;
      case 'd':
        loop4();
        break;
      default:
        // turn all the LEDs on:
        for (j = 0; j < 8; j++) {
          pixels.setPixelColor(j, pixels.Color(255,255,255)); 
           pixels.show();
        }
    }
  }
  delay(1);        // delay in between reads for stability
}

