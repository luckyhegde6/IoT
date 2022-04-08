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

void setup()
{
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop()
{

  for (int i = 0; i < NUMPIXELS; i++)
  {
    for (int j = 0; j < 255; j++)
    { for (int k = 0; k < 255; k++)
      { for (int l = 0; l < 255; l++)
        { pixels.setPixelColor(i, j, k, l);//To set the 8th pixel (#7, counting from 0) to magenta (red + blue)
          pixels.show();
          //delay(500);
        }
      }
    }
  }
}
