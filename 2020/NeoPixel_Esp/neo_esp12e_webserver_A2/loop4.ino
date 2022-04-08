 void loop4()
 {
  // read the potentiometer:
  int sensorReading = analogRead(analogPin);
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(sensorReading, 0, 1023, 0, ledCount);

  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevel) {
      //digitalWrite(ledPins[thisLed], HIGH);
      pixels.setPixelColor(ledPins[thisLed], pixels.Color(255,0,0)); 
      pixels.show();
    }
    // turn off all pins higher than the ledLevel:
    else {
      //digitalWrite(ledPins[thisLed], LOW);
       pixels.setPixelColor(ledPins[thisLed], pixels.Color(0,0,0)); 
    }
  }
  }
