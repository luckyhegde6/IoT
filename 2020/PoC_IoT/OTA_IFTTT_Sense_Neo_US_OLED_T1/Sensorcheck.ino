void Sensorcheck()
{
  if (distance >0 && distance <= Range)
{
   Serial.print("distance: ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println(" ");
    obj = true;
    objval = 1;
    digitalWrite(led, HIGH);   //the led visualizes the sensors output pin state
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(distance,255-distance,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(5); // Delay for a period of time (in milliseconds).
  }
}
  else {
    Serial.println("Out of Range");
    obj = false;
    objval = 0;
    digitalWrite(led, LOW);  //the led visualizes the sensors output pin state
for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(5); // Delay for a period of time (in milliseconds).
  
    }
}
}
