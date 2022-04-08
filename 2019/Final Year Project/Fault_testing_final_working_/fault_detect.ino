int fault_detect()
{
 // if it is, the buttonState is HIGH:
 if (buttonState1 == HIGH) 
  {lcd_keypad();
      flg=1;
      flu=1;
  }
else if (buttonState2 == HIGH) 
  {  gsm_fault(1);
     lcd_keypad();
     flg=1;
     flu=0;
     fault_display();
     }
else if (buttonState3 == HIGH) 
  {  gsm_fault(2);
     lcd_keypad();
     flg=1;
     flu=0;
     fault_display();
  }
  
  else if (buttonState4 == HIGH) 
  {  gsm_fault(3);
     lcd_keypad();
     flg=1;
     flu=0;
     fault_display();
  }
  else if (buttonState5 == HIGH) 
  {  gsm_fault(4);
     lcd_keypad();
     flg=1;
     flu=0;
     fault_display();
  }
  
  else
  {
  lcd.clear();
    lcd.print("Sensor error");
    lcd.setCursor(0,1);
  lcd.print("Check connections");
  }
}

