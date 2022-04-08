#include <Adafruit_NeoPixel.h>
#define PIN            14
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(30);
  Serial.begin(115200);
}

void loop() {

 int i =0; // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
while(i<255){
  int j =0;
  while(  j <= NUMPIXELS){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(j, pixels.Color(255-i,0,i)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(100); // Delay for a period of time (in milliseconds).
  j++;
   Serial.print("Valiue of j =");
   Serial.print(j);
    Serial.print("\n");
  }
  i= i+5;
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();
  delay(200);
  Serial.print("Valiue of I =");
   Serial.print(i);
    Serial.print("\n");
  
}
}
