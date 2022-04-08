                        
void setup()

{    


Serial.begin(9600);
  pinMode(P1_4, OUTPUT);       

}

  void loop()

{

   digitalWrite(P1_4,0);           // Turns ON Relays 1
   Serial.println("Light ON");
   delay(2000);                                      // Wait 2 seconds

   digitalWrite(P1_4,1);          // Turns Relay Off
   Serial.println("Light OFF");
   delay(2000);
   
}
