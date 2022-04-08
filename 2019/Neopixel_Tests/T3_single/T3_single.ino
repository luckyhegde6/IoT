#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN  14

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel pixelss you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int i=0;
int j=0;
void setup()
{
 pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
/*
  for(int i=0;i<NUMPIXELS;i++){
   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(i,i,i)); // Moderately bright green color.
    pixels.show();
    //pixels.setPixelColor(n, red, green, blue, white);
    //pixels.setPixelColor(n, red, green, blue, white);
  }*/
 
if (i<8)
{
while (j<255)
{pixels.setBrightness(50); //The overall brightness of all the LEDs can be adjusted using setBrightness(). This takes a single argument, a number in the range 0 (off) to 255 (max brightness). For example, to set a pixels to 1/4 brightness:
pixels.setPixelColor(i, j,255-j, 255-j);
pixels.setPixelColor(i+1, j,255-j, 255-j);
pixels.setPixelColor(i+2, j,255-j, 255-j);
pixels.setPixelColor(i+3, j,255-j, 255-j);
pixels.setPixelColor(i+4, j,255-j, 255-j);
pixels.setPixelColor(i+5, j,255-j, 255-j);
pixels.setPixelColor(i+6, j,255-j, 255-j);
j++;
 delay(100);
 pixels.show(); 
}
}
else
{
  i=0;
}


//delay(delayval); // Delay for a period of time (in milliseconds).


}
