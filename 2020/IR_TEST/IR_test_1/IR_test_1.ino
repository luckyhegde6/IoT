int led1 = 13;
void setup()
{
     pinMode(A0, INPUT);
     pinMode(led1, OUTPUT);
     Serial.begin(9600);
 }

void loop()
{
  int sensorValue = analogRead(A0);
  int readsen = digitalRead(A0);
  Serial.println(sensorValue);
    if( readsen == HIGH )
     {
       digitalWrite(led1, HIGH);
     }
else
     {
       digitalWrite(led1, !HIGH);
      }
delay(100);
}

/* THE END */
