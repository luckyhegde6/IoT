// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(14, OUTPUT);
  pinMode(12, INPUT);
 // pinMode(13, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  int a = digitalRead(12);
  if (a == 0)
  {digitalWrite(14, HIGH);// turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(14, LOW);// turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  }
  else
  {
    digitalWrite(14, HIGH);// turn the LED on (HIGH is the voltage level)
  }
  
}

