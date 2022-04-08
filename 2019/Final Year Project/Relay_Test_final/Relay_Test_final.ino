int pushButton = P2_0;
const int ledPin =  P1_6;      // the number of the LED pin
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800
  // make the on-board pushbutton's pin an input pullup:
  pinMode(pushButton, INPUT_PULLUP);
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
   if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, LOW);
  Serial.println(" No Fault found");  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
   Serial.println("Fault Detected\n");  
  }
  delay(1000);
}
