// digital pin 12 has a Sensor attached to it. Give it a name:
int Sensorpin = 12;
int SenseRead[300] = {};
long arraySum =0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // make the pushbutton's pin an input:
  pinMode(Sensorpin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  // read the input pin:
  for (int i =0;i<60;i++)
  {
  int sensorval = digitalRead(Sensorpin);
  SenseRead[i] = sensorval;
  // print out the state of the button:
  Serial.print("Sensor state: ");
  Serial.print(sensorval);
  Serial.println(" ");
  delay(1000); 
  Serial.print("Sensor value: ");
  Serial.print(SenseRead[i]);
  Serial.println(" ");
   Serial.print("Array Sum:");
   arraySum +=  SenseRead[i];
  Serial.print(arraySum);
  Serial.println(" ");
         // delay in between reads for stability
  }
Serial.print("1 mins done: ");
/*if( arraySum > 30)
{
  Serial.print("Array Sum:");
  Serial.print(arraySum);
  Serial.println("object dected"); 
}
else
{
  Serial.print("Array Sum:");
  Serial.print(arraySum);
  Serial.println(" no object dected"); 
}*/
int range = map(arraySum, 0, 60, 0, 3);
  switch (range) {
    case 0:    // your hand is on the sensor
      Serial.print("Array Sum:");
  Serial.print(arraySum);
  Serial.println(" no object dected"); 
      break;
    case 1:    // your hand is close to the sensor
      Serial.print("Array Sum:");
  Serial.print(arraySum);
  Serial.println("object dected"); 
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
      break;
    case 2:    // your hand is a few inches from the sensor
      Serial.print("Array Sum:");
  Serial.print(arraySum);
  Serial.println("moving object dected"); 
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);      
      break;
    case 3:    // your hand is nowhere near the sensor
      Serial.print("Array Sum:");
  Serial.print(arraySum);
  Serial.println("object stable"); 
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for a second 
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW   
      break;
  }
 arraySum = 0;
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}



