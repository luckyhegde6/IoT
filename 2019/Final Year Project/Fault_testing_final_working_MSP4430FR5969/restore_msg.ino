int restore_msg(int hr)
{
  switch(hr)
  {
    case 1:
     { Serial.println("AT\r\n");
       delay(200);
      Serial.println("AT+HVOIC;\r\n");
       delay(200);
      Serial.println("AT+CMGF=1;\r\n");
       delay(200);
      Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
       delay(200);                                  
      Serial.println("Power will be restored in 1 hour\x1A"); //SMS to your Mobile Number
       delay(200);
       break;
     }
     
      case 2:
     { Serial.println("AT\r\n");
       delay(200);
      Serial.println("AT+HVOIC;\r\n");
       delay(200);
      Serial.println("AT+CMGF=1;\r\n");
       delay(200);
      Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
       delay(200);                                  
      Serial.println("Power will be restored in 2 hour\x1A"); //SMS to your Mobile Number
       delay(200);
       break;
     }
     
      case 3:
     { Serial.println("AT\r\n");
       delay(200);
      Serial.println("AT+HVOIC;\r\n");
       delay(200);
      Serial.println("AT+CMGF=1;\r\n");
       delay(200);
      Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
       delay(200);                                  
      Serial.println("Power will be restored in 3 hour\x1A"); //SMS to your Mobile Number
       delay(200);
       break;
     }
  
      default:
     { Serial.println("AT\r\n");
       delay(200);
      Serial.println("AT+HVOIC;\r\n");
       delay(200);
      Serial.println("AT+CMGF=1;\r\n");
       delay(200);
      Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
       delay(200);                                  
      Serial.println("if power is not restored contact Electricity Board\x1A"); //SMS to your Mobile Number
       delay(200);
    
     }
  }
}
