void Motiondetect()
{
if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state       
       obj = true;
    objval = 1;
    Serial.println("Movement Present");
      display.clearDisplay();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
      display.println("Movement Present");
      display.display();
      display.clearDisplay();
}
  else {
    obj = false;
    objval = 0;
    Serial.println("No Movements");
      display.clearDisplay();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
      display.println("no Movements");
      display.display();
      display.clearDisplay();
    digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state              
       }
  // read the PIR input pin:
  State = objval;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = State;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
int stable = total / numReadings;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // compare the buttonState to its previous state
  if (State != lastState) {
    // if the state has changed, increment the counter
    if (State == 1) {
      // if the current state is HIGH then the button
      // wend from off to on:
      Counter++;
      Serial.println("Movement");
      Serial.print("number of state change:  ");
      Serial.println(Counter);
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    for(int i=0; i<10; i++)
    {
      Serial.print(readings[i]);
      Serial.print(" ");
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastState = State;
  if(stable == 1)
  {Firebase.setString("PIR_Sensor Status", "Room is Occupied");}
  else if(total == 0){Firebase.setString("PIR_Sensor Status", "Room is not Occupied");}
  else{}
}
