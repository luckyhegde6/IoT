#include <Adafruit_NeoPixel.h>

#define PIN 4
int i,count=0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
void loop() {
  // Some example procedures showing how to display to the pixels:
  while (count<8){
  for(i=0; i<8; i++) {
    int r,g,b;
    r=i*25; g=255-r; b=255-g;
    strip.setPixelColor(i, strip.Color(r,g,b));
    strip.show();
//    delay(200);
//    strip.setPixelColor(i, strip.Color(150,0,0));
//    strip.show();
//    delay(200);
//    strip.setPixelColor(i, strip.Color(0,0,150));
//    strip.show();
//    delay(200);
    strip.setPixelColor(i, strip.Color(25,25,35));
    delay(200);
}
strip.show();
count ++;
Serial.println("count is: ");
Serial.println(count);

  }
  count =0;
}
