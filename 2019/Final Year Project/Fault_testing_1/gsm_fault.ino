
void gsm_fault(char fault ){
   switch (fault)
   {case "fault1":{ 
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
   
     Serial.println("\n");
     Serial.println("button1 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState1);
 Serial.println("\n");
  Serial.println("\nbutton2 =");
     Serial.println("\n");
   Serial.print(buttonState2);
   Serial.println("button3 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState3);
 Serial.println("\n");
  Serial.println("\nbutton4 =");
     Serial.println("\n");
   Serial.print(buttonState4);
     Serial.println("\nbutton5 =");
     Serial.println("\n");
   Serial.print(buttonState5);
     Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9886991029");
   Serial.print('"');
  Serial.print('\r');
   Serial.print("L-G Fault found");
  Serial.write(26);
  delay(5000);
  break;
  } 
  case "fault2" :
  {
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
     delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
   
     Serial.println("\n");
     Serial.println("button1 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState1);
 Serial.println("\n");
  Serial.println("\nbutton2 =");
     Serial.println("\n");
   Serial.print(buttonState2);
   Serial.println("button3 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState3);
 Serial.println("\n");
  Serial.println("\nbutton4 =");
     Serial.println("\n");
   Serial.print(buttonState4);
     Serial.println("\nbutton5 =");
     Serial.println("\n");
   Serial.print(buttonState5);
   Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9886991029");
   Serial.print('"');
  Serial.print('\r');
   Serial.print("L-L Fault found");
  Serial.write(26);
  delay(5000);
  break;
  }
    case "fault3" :
  {
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
     delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
      delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
   
     Serial.println("\n");
     Serial.println("button1 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState1);
 Serial.println("\n");
  Serial.println("\nbutton2 =");
     Serial.println("\n");
   Serial.print(buttonState2);
   Serial.println("button3 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState3);
 Serial.println("\n");
  Serial.println("\nbutton4 =");
     Serial.println("\n");
   Serial.print(buttonState4);
     Serial.println("\nbutton5 =");
     Serial.println("\n");
   Serial.print(buttonState5);
   Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9886991029");
   Serial.print('"');
  Serial.print('\r');
   Serial.print("L-L-G fault found");
  Serial.write(26);
  delay(5000);
  break;
  }
  
   case "fault4" :
  {
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
     delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
     delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
     delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
   
     Serial.println("\n");
     Serial.println("button1 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState1);
 Serial.println("\n");
  Serial.println("\nbutton2 =");
     Serial.println("\n");
   Serial.print(buttonState2);
   Serial.println("button3 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState3);
 Serial.println("\n");
  Serial.println("\nbutton4 =");
     Serial.println("\n");
   Serial.print(buttonState4);
     Serial.println("\nbutton5 =");
     Serial.println("\n");
   Serial.print(buttonState5);
   Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9886991029");
   Serial.print('"');
  Serial.print('\r');
   Serial.print("3phase fault found");
  Serial.write(26);
  delay(5000);
  break;
  }
  default:
  {
     Serial.println("\n");
     Serial.println("button1 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState1);
 Serial.println("\n");
  Serial.println("\nbutton2 =");
     Serial.println("\n");
   Serial.print(buttonState2);
   Serial.println("button3 =\n"); 
     Serial.println("\n");
   Serial.print(buttonState3);
 Serial.println("\n");
  Serial.println("\nbutton4 =");
     Serial.println("\n");
   Serial.print(buttonState4);
     Serial.println("\nbutton5 =");
     Serial.println("\n");
   Serial.print(buttonState5);
   Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9886991029");
   Serial.print('"');
  Serial.print('\r');
   Serial.print("NO fault found");
  Serial.write(26);
  delay(5000);
  }
   }
}
