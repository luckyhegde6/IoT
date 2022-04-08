#define RED_PIN 9      // where the red pin is connected to
#define GREEN_PIN 10   // where the green pin is connected to
#define BLUE_PIN 11    // where the blue pin is connected to
#define DELAY 20       // 20ms internal delay; increase for slower fades

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  // fade from green to red
  for(int i=0; i<255; i++) {
    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, 255-i);
    analogWrite(BLUE_PIN, 0);
    delay(DELAY);
  }

  // fade from red to blue
  for(int i=0; i<255; i++) {
    analogWrite(RED_PIN, 255-i);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, i);
    delay(DELAY);
  }

  // fade from blue to green
  for(int i=0; i<255; i++) {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, 255-i);
    delay(DELAY);
  }
}
