void loop1(){
  pixels.setPixelColor(j, pixels.Color(0,0,0)); 
      pixels.show(); 
for (j=0;j<NUMPIXELS;j++){
  
  // fade from green to red
  for(int i=0; i<255; i++) {
     pixels.setPixelColor(j, pixels.Color(i,255-i,0)); 
      pixels.show(); 
    delay(DELAY);
  }

  // fade from red to blue
  for(int i=0; i<255; i++) {
       pixels.setPixelColor(j, pixels.Color(255-i,0,i)); 
        pixels.show(); 
    delay(DELAY);
  }

  // fade from blue to green
  for(int i=0; i<255; i++) {
     pixels.setPixelColor(j, pixels.Color(i,0,255-i)); 
      pixels.show(); 
    delay(DELAY); 
  }
  pixels.setPixelColor(j, pixels.Color(0,0,0)); 
      pixels.show(); 
   }

}
