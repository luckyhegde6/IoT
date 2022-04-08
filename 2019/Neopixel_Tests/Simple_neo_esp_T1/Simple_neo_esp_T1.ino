#include <Adafruit_NeoPixel.h>
#define PIN 14
#define NUMPIXELS 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
void setup()
{
  strip.begin();
//  strip.show(); // Initialize all pixels to 'off'
//  strip.setPixelColor(n, red, green, blue);
//  strip.setPixelColor(n, red, green, blue, white);
//  strip.setPixelColor(11, 255, 0, 255);
//  strip.setPixelColor(7, 0, 0, 0, 127);
//  strip.setPixelColor(n, color);
// uint32_t magenta = strip.Color(255, 0, 255);
// uint32_t greenishwhite = strip.Color(0, 64, 0, 64);
// uint32_t color = strip.getPixelColor(11);
// strip.show();
// uint16_t n = strip.numPixels();
// strip.setBrightness(64);
// Adafruit_NeoPixel strip_a = Adafruit_NeoPixel(16, 5);
//Adafruit_NeoPixel strip_b = Adafruit_NeoPixel(16, 6);
}
void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<255;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(i,i,i)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}
