void fault_display() {
  if (buttonState2 == HIGH) 
  {  digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
      lcd.clear();
     lcd.print("  LG Fault");
     lcd.setCursor(0,1);
  lcd.print("Press * to clear");
     }
else if (buttonState3 == HIGH) 
  {  digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
     delay(200);
     digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
      lcd.clear();
     lcd.print("  LLG Fault");
     lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  }
  
  else if (buttonState4 == HIGH) 
  {  digitalWrite(ledPin1, HIGH);
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
      lcd.clear();
     lcd.print("  LL Fault");
     lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  }
  else if (buttonState5 == HIGH) 
  {  digitalWrite(ledPin1, HIGH);
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
      lcd.clear();
    lcd.print("  3-Ph Fault");
   lcd.setCursor(0,1);
  lcd.print("Press * to clear"); 
  }
  else if(buttonState1 == HIGH)
  { lcd.clear();
  lcd.print("  NO Fault");
 lcd.setCursor(0,1);
  lcd.print("Press * to clear");
   } 
 }  
