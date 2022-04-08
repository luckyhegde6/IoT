//define the pins
#define LED  13
int PIR = 5;
int Buzzer = 4;

void setup() {
  Serial.begin(9600);
  //define the LED and Buzzer pin as output
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  //define the sensor pin as input
  pinMode(PIR, INPUT);
}

void loop() {
  //using the digitalRead function we will read the signal of the sensor
  int value = digitalRead(PIR);
  delay(1000);
  //if its high or if an any object is detected it will activate the LED and Buzzer
  if (value == HIGH){
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    Serial.println(value);
    Serial.println("Motion Detected");

  }
  else {
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, LOW);
    Serial.println(value);
  }
}
