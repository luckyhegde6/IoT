#include <Adafruit_NeoPixel.h>

#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
unsigned int rgbColour[3] = {0, 0, 0};
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
 // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      int incColour = decColour == 2 ? 0 : decColour + 1;
      pixels.setPixelColor(i, pixels.Color(rgbColour[0], rgbColour[1], rgbColour[2])); // Moderately bright green color.
      //setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(50);
            pixels.show(); 
    }
  }
}

