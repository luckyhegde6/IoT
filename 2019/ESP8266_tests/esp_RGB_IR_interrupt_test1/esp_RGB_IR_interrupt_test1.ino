/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
int redPin = 12;
int bluePin = 13;
int greenPin = 14;

int redIn = 0;
int greenIn = 1;
int blueIn = 2;

int redVal;
int greenVal;
int blueVal;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
   pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  
  
}
// This function updates the LED outputs.
void update()
{// Flash festive lights
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    delay(100);
    digitalWrite(14, LOW);
    digitalWrite(13, HIGH);
    delay(100); 
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    delay(100);
}


// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  if( sensorValue == 1024)
  {
  update();
  }
 
  else{digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);}
  delay(200);
}
