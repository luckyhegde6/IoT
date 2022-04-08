 int fault_detect()
{
 // if it is, the buttonState is HIGH:
 if (buttonState1 == HIGH) 
  {
      flg=1;
      flu=1;
      lcd_keypad();
  }
else if (buttonState2 == HIGH) 
  {  gsm_fault(1);
     flg=1;
     flu=0;
     fault_display();
     delay(3000);
     flg=0;
     lcd_keypad();
     }
else if (buttonState3 == HIGH) 
  {  gsm_fault(2);
     lcd_keypad();
     flg=1;
     flu=0;
     fault_display();
     delay(3000);
     flg=0;
  }
  
  else if (buttonState4 == HIGH) 
  {  gsm_fault(3);
     flg=1;
     flu=0;
     fault_display();
     delay(3000);
     flg=0;
     lcd_keypad();
  }
  else if (buttonState5 == HIGH) 
  {  gsm_fault(4);
     flg=1;
     flu=0;
     fault_display();
     delay(3000);
     flg=0;
     lcd_keypad();
  }
}

