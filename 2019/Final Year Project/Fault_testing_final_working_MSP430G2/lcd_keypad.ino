void lcd_keypad(){
  int restore_msg(int hr);
   char key = kpd.getKey();
 if (key == '*')
  {
    flg=0;
    flu=0;
    lcd.clear();
   }
  
   if (key == '1')
   {
    restore_msg(1);
    lcd.clear();
    lcd.print("  Pwr rst in 1 hr");
    lcd.setCursor(0,1);
    lcd.print("Press * to clear");
    
    }
  
  if (key == '2')
   {
    restore_msg(2);
    lcd.clear();
    lcd.print("Pwr rst in 2 hr");
    lcd.setCursor(0,1);
    lcd.print("Press * to clear");
    }
  
  if (key == '3')
  {
    restore_msg(3);
    lcd.clear();
    lcd.print("Pwr rst in 3 hr");
    lcd.setCursor(0,1);
    lcd.print("Press * to clear");
    }
  
  if (key == 'A')
  {
   lcd_keypad();
   lcd.clear();
   flg=1;
   flu=0;
   }
  if (key == 'B')
  {
   lcd_keypad();
   lcd.clear();
   flg=0;
   flu=0;
   }
   if (key == 'C')
   {
    lcd_keypad();
    lcd.clear();
    lcd.print("Checking faults");
    flg=1;
    if(buttonState1 == HIGH)
    {
      restore_msg(5);
      lcd.clear();
      lcd.print("  MSG SENT\x1A");
      delay(5000);
      flu=0;
      lcd_keypad();
     
    }
  else
  {
   lcd_keypad();
   lcd.clear();
   lcd.print("fault Still exists");
   flg=1;
   }
  }
  
  if (key == 'D')
  {
    flg=0;
    flu=0;
    lcd_keypad();
    lcd.clear();
    lcd.print("Dept.of EEE NMIT");
    lcd.setCursor(0,1);
    lcd.print("Project AFDS");
  }
 
 }
