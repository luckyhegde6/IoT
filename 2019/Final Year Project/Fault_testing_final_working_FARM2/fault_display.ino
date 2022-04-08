void fault_display() {
  if (buttonState2 == HIGH) 
  {  digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
      lcd.clear();
     lcd.print("  L-G Fault");
     lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  delay(200);
  Serial.print("L-G FAULT\n");
  delay(300);
     flg=0;
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
     lcd.print("  L-L-G Fault\n");
     lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  delay(200);
  Serial.print("L-L-G FAULT\n");
    delay(300);
     flg=0;
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
     lcd.print("  L-L Fault");
     lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  delay(200);
  Serial.print("L-L FAULT\n");
    delay(300);
     flg=0;
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
  delay(200);
  Serial.print("3 phase FAULT\n");
   delay(300);
     flg=0; 
  }
  else if(buttonState1 == HIGH)
  { lcd.clear();
  lcd.print("  NO Fault");
 lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  delay(200);
  Serial.print("NO FAULT\n");
   }
 else if(buttonState1 == LOW && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == LOW)
  {
  lcd.clear();
    lcd.print("  Sensor error");
    lcd.setCursor(0,1);
  lcd.print("Check connections");
  delay(200);
  Serial.println("Sensor Error\n");
  } 
 }  
