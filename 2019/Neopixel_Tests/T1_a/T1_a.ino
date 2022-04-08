
#include <Adafruit_NeoPixel.h>

#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
unsigned int rgbColour[3] = {0, 0, 0};

int state = 0;
int a = 255;
int r = 255;
int g = 0;
int b = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
}
void loop() {
  for (int i=0;i<NUMPIXELS;i++){
if(state == 0){
    g++;
    if(g == 255)
        state = 1;
}
if(state == 1){
    r--;
    if(r == 0)
        state = 2;
}
if(state == 2){
    b++;
    if(b == 255)
        state = 3;
}
if(state == 3){
    g--;
    if(g == 0)
        state = 4;
}
if(state == 4){
    r++;
    if(r == 255)
        state = 5;
}
if(state == 5){
    b--;
    if(b == 0)
        state = 0;
}
int hex = (a << 24) + (r << 16) + (g << 8) + (b);
state =hex;

 pixels.setPixelColor(i, pixels.Color(rgbColour[r], rgbColour[g], rgbColour[b])); // Moderately bright green color.
      //setColourRgb(rgbColour[r], rgbColour[g], rgbColour[b]);
      delay(50);
            pixels.show(); 
}
}
