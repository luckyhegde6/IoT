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
    pixels.setPixelColor(7, 255, 0, 255);//To set the 8th pixel (#7, counting from 0) to magenta (red + blue)
 pixels.show(); 
    delay(1000);

    //to set the 8th pixel (#7 counting from 0) to half-brightness white, with no light from red/green/blue,
        pixels.setPixelColor(7, 0, 0, 0, 127);
         pixels.show(); 
         
    //An alternate syntax has just two arguments: pixels.setPixelColor(n, color);
    uint32_t magenta = pixels.Color(255, 0, 255);  //convert separate red, green and blue values into a single 32-bit type for later use
 pixels.show(); 
    delay(1000);
    uint32_t greenishwhite = pixels.Color(0, 64, 0, 64);  //add a white component to the color at the end
 pixels.show(); 
    delay(1000);
    uint32_t color = pixels.getPixelColor(6); // query the color of a previously-set pixel using getPixelColor(): 
 pixels.show(); 
    delay(1000);
    uint16_t n = pixels.numPixels();//The number of pixels in a previously-declared pixels can be queried using numPixels(): 
     pixels.show(); 
    delay(1000);
    pixels.setBrightness(64); //The overall brightness of all the LEDs can be adjusted using setBrightness(). This takes a single argument, a number in the range 0 (off) to 255 (max brightness). For example, to set a pixels to 1/4 brightness:
    pixels.show(); // This sends the updated pixel color to the hardware.
// Adafruit_NeoPixel pixels_a = Adafruit_NeoPixel(16, 5);
//Adafruit_NeoPixel pixels_b = Adafruit_NeoPixel(16, 6);
//The above declares two distinct NeoPixel objects, one each on pins 5 and 6, each containing 16 pixels and using the implied default type (NEO_KHZ800 + NEO_GRB). 
    //delay(delayval); // Delay for a period of time (in milliseconds).


}
