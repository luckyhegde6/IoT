int gsm_fault(int fault ){
   switch (fault)
   {case 1:{ 
     
     Serial.println("AT\r\n");
      delay(200);
     Serial.println("AT+HVOIC;\r\n");
      delay(200);
     Serial.println("AT+CMGF=1;\r\n");
      delay(200);
     Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);
     Serial.println("L-G Fault found\x1A"); //SMS to your Mobile Number
     delay(6000);
     Serial.println("\n");
      Serial.println("AT+CMGS=\"9480789220\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);
     Serial.println("L-G Fault found\x1A"); //SMS to your Mobile Number
     delay(2000);
      lcd_keypad();
      break;
    } 
  case 2 :
  {
      Serial.println("AT\r\n");
      delay(200);
     Serial.println("AT+HVOIC;\r\n");
     delay(200);
     Serial.println("AT+CMGF=1;\r\n");
      delay(200);
     Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);                                  
     Serial.println("L-L-G Fault found\x1A"); //SMS to your Mobile Number
      delay(6000);
       Serial.println("\n");
      Serial.println("AT+CMGS=\"9480789220\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);
     Serial.println("L-L-G Fault found\x1A"); //SMS to your Mobile Number
     delay(2000);
      lcd_keypad();
      break;
    }
    case 3 :
  {
     Serial.println("AT\r\n");
      delay(200);
     Serial.println("AT+HVOIC;\r\n");
      delay(200);
     Serial.println("AT+CMGF=1;\r\n");
      delay(200);
     Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);                                  
     Serial.println("L-L Fault found\x1A"); //SMS to your Mobile Number
      delay(6000);
       Serial.println("\n");
      Serial.println("AT+CMGS=\"9480789220\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);
     Serial.println("L-L Fault found\x1A"); //SMS to your Mobile Number
     delay(2000);
      lcd_keypad();
      break;
     }
  
   case 4 :
  {
      Serial.println("AT\r\n");
       delay(200);
     Serial.println("AT+HVOIC;\r\n");
      delay(200);
    Serial.println("AT+CMGF=1;\r\n");
      delay(200);
    Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
     delay(200);                                  
    Serial.println("3-Ph Fault found\x1A"); //SMS to your Mobile Number
     delay(6000);
      Serial.println("\n");
      Serial.println("AT+CMGS=\"9480789220\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);
     Serial.println("3-Ph Fault found\x1A"); //SMS to your Mobile Number
     delay(2000);
     lcd_keypad();
     break;
     }
     case 5 :
  {
      Serial.println("AT\r\n");
       delay(200);
     Serial.println("AT+HVOIC;\r\n");
      delay(200);
    Serial.println("AT+CMGF=1;\r\n");
      delay(200);
    Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
     delay(200);                                  
    Serial.println("Fault Cleared\x1A"); //SMS to your Mobile Number
     delay(2000);
     lcd_keypad();
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
      Serial.println("\n");
      Serial.println("button3 =\n"); 
      Serial.println("\n");
      Serial.print(buttonState3);
      Serial.println("\n");
      Serial.println("\nbutton4 =");
      Serial.println("\n");
      Serial.print(buttonState4);
      Serial.println("\n");
      Serial.println("\nbutton5 =");
      Serial.println("\n");
      Serial.print(buttonState5);
      Serial.println("\n");
      Serial.println("AT\r\n");
      delay(200);
      Serial.println("AT+HVOIC;\r\n");
      delay(200);
      Serial.println("AT+CMGF=1;\r\n");
      delay(200);
     Serial.println("AT+CMGS=\"98036758418\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);                                  
     Serial.println("No Fault found\x1A"); //SMS to your Mobile Number
     delay(6000);
      Serial.println("\n");
      Serial.println("AT+CMGS=\"9480789220\";\r\n"); //Enter Mobile Number between double " " codes.
      delay(200);
     Serial.println("No Fault found\x1A"); //SMS to your Mobile Number
     delay(2000);
     lcd_keypad();
    }
   }
}

