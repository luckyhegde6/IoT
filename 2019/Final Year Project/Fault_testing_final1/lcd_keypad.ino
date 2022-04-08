void lcd_keypad(){
  int restore_msg(int hr);
   char key = kpd.getKey();
  //if (key){
  //  lcd.print(key);
    // }
  if (key == '*')
  {
    flg=0;
    flu=0;
  lcd.clear();
  }
  
   if (key == '1'){
    restore_msg(1);
    lcd.clear();
    lcd.print("Pwr restore in 1 hr");
    lcd.setCursor(0,1);
  lcd.print("Press * to clear");
    
  }
  
  if (key == '2'){
    restore_msg(2);
    lcd.clear();
    lcd.print("Pwr restore in 2 hr");
    lcd.setCursor(0,1);
  lcd.print("Press * to clear");
    
  }
  
  if (key == '3'){
    restore_msg(3);
    lcd.clear();
    lcd.print("Pwr restore in 3 hr");
    lcd.setCursor(0,1);
  lcd.print("Press * to clear");
    
  }
  
   if (key == 'C'){
    
  lcd_keypad();
  lcd.clear();
  lcd.print("Checking faults");
  flu=1;
  fault_detect();
  restore_msg(5);
  flu=0;
  }
  
  if (key == 'D'){
    flg=0;
    flu=0;
  lcd_keypad();
  lcd.clear();
  lcd.print("Dept.of EEE NMIT");
  lcd.setCursor(0,1);
  lcd.print("Press * to clear");
  }
  
  if (key == 'A'){
  lcd_keypad();
  lcd.clear();
  flg=1;
   flu=0;
  
  }
  if (key == 'B'){
  lcd_keypad();
  lcd.clear();
  flg=0;
   flu=0;
  }
  
 
    
}
