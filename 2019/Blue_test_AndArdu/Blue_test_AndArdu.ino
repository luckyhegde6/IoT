
GET digitalWrite DATA FROM ARDUDROID
  if (ard_command == CMD_DIGITALWRITE){ 
    if (pin_value == PIN_LOW) pin_value = LOW;
    else if (pin_value == PIN_HIGH) pin_value = HIGH;
    else return; // error in pin value. return.
    set_digitalwrite( pin_num,  pin_value);  // call function to process digital pin#
    return;  // return from start of loop()
  }

// 2a) select the requested pin# for DigitalWrite action
void set_digitalwrite(int pin_num, int pin_value)
{
  switch (pin_num) {
  case 13:
    pinMode(13, OUTPUT);
    digitalWrite(13, pin_value); 
    // add your code here     
    break;
case 2: pinMode(2, OUTPUT);
    digitalWrite(2, pin_value);
    // add your code here      
    break;     
    // default:
    // if nothing else matches, do the default
    // default is optional
  } }
 // 3) GET analogWrite DATA FROM ARDUDROID
  if (ard_command == CMD_ANALOGWRITE)
  { 
    analogWrite(  pin_num, pin_value );
    // add your code here
    return;  // Done. return to loop();
  }

// 1) GET TEXT COMMAND FROM ARDUDROID
  if (ard_command == CMD_TEXT)
  {  
    inText ="";  //clears variable for new input  
    while (Serial.available())  {
      char c = Serial.read();  //gets one byte from serial buffer
      delay(5);
      if (c == END_CMD_CHAR) { // if we the complete string has been read
        // add your code here
        break;
      }             
      else {
        if (c !=  DIV_CMD_CHAR)
        {
          inText += c;
          delay(5);}
          }
        }
       }
// 4) SEND DATA TO ARDUDROID
  if (ard_command == CMD_READ_ARDUDROID)
  {
    // char send_to_android[] = "Place your text here." ;
    // Serial.println(send_to_android);   // Example: Sending text
    Serial.print(" Analog 0 = ");
    Serial.println(analogRead(A0));  // Example: Read and send Analog pin value to Arduino
    return;  // Done. return to loop();
  }
