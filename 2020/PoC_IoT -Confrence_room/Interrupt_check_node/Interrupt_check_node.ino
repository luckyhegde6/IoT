const byte ledPin = 1;
const byte interruptPin = 13;
volatile byte state = LOW;

void setup() {
   Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
 
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
  Serial.println("LED State: ");
  Serial.println(state);
}
