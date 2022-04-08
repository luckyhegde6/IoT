#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
int i;
if (i<8)
{
  for( i=0;i<NUMPIXELS;i++){
int c = setC(i);
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i,c); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

   delay(delayval); // Delay for a period of time (in milliseconds).

  }
}
  else i=0;

}
  int setC(int j)
  {
    if (j<7)
    {
    for (int i=0;i<255;i++)
    {
    return pixels.Color(255-i,255-i,255-i);}
    }
    else 
    {return pixels.Color(0,150,0);}
  }
