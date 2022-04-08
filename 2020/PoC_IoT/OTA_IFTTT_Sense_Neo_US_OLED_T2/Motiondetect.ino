void Motiondetect()
{
  
if (distance >0 && distance <= Range)
{
   Serial.print("distance: ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println(" ");
      display.clearDisplay();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
      display.print("distance: ");
    display.print(distance);
    display.print(" cm");
      display.display();
    obj = true;
    objval = 1;
    digitalWrite(led, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;           
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         ifttt.triggerEvent(EVENT_NAME2,"Motion detected at",String(millis()/1000)+" Sec");
           display.clearDisplay();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
      display.print("motion detected at ");
         display.print(millis()/1000);
         display.println(" sec");
      display.display();
      delay(500);
      display.clearDisplay();
         }        
         takeLowTime = true;
         delay(10);
         ReadState();
         Serial.println("");
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(distance,255-distance,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(5); // Delay for a period of time (in milliseconds).
  }
  }
  else {
    Serial.println("Out of Range");
      display.clearDisplay();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
      display.println("Out of Range");
      display.display();
    obj = false;
    objval = 0;
    digitalWrite(led, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause)
       {
        //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;               
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           
           ifttt.triggerEvent(EVENT_NAME2,"Motion ended at",String((millis() - pause)/1000) + " Sec");
             
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
     display.print("motion ended at ");      //output
           display.print((millis() - pause)/1000);
           display.println(" sec");
      display.display();
      delay(500);
      display.clearDisplay();
         }
         
         for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(5); // Delay for a period of time (in milliseconds).
  
    }
    
         }
}
