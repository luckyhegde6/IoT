
void lcd_keypad(){
   char key = kpd.getKey();
  if (key){
    Serial.println(key);
    lcd.print(key);
    
  }
  if (key == '*')
  {
  lcd.clear();
  }
    
}
