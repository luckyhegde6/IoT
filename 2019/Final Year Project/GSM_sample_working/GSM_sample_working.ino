void setup()
{
  Serial.begin(9600);  //Baud rate of the GSM/GPRS Module
Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9886991029");
   Serial.print('"');
  Serial.print('\r');
  Serial.print("GSM TEST SMS");
   Serial.print("Yo Shetty we did it!!!");
  Serial.write(26);
  delay(5000);


}

void loop()
{}
