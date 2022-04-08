void setup() {
 // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    while (Serial.available() > 0) {
      // display each character to the LCD
      Serial.read();
    }
  }
}
