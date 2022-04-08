#include <Keypad_I2C.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x38,16,2);  // set the LCD address to 0x38 for a 16 chars and 2 line display
const byte ROWS = 4; 
const byte COLS = 4; 
int flg;   //flag for fault_display 
int flu;   // flag for msg sending i.e fault_detect
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {0,1,2,3}; 
byte colPins[COLS] = {4,5,6,7};

int i2caddress = 0x3F;

Keypad_I2C kpd = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, i2caddress );
const int buttonPin1 = P1_4;     // the number of the fault input pin
const int buttonPin2 = P1_5;     // the number of the fault input pin
const int buttonPin3 = P2_0;    // the number of the fault input pin
const int buttonPin4 = P2_1;    // the number of the fault input pin
const int buttonPin5 = P2_2;    // the number of the fault input pin


// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
int buttonState4 = 0;         // variable for reading the pushbutton status
int buttonState5 = 0;         // variable for reading the pushbutton status
const int ledPin1 =  RED_LED;      // the number of the LED pin
int gsm_fault(int fault);
void lcd_keypad();
int restore_msg(int hr);
void setup(){   
  
  pinMode(buttonPin1, INPUT);// initialize the relaypin pin as an input:
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(ledPin1, OUTPUT);  // initialize the LED pin as an output:
 lcd.init();  
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.noBacklight(); // finish with backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Welcome to AFDS "); //Automatic fault detection system
  delay(3000);  

// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("   Use keypad");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("Press * to clear");  
 kpd.begin();
 
  lcd_keypad();
  flg=0;
 flu=1;
  

}
void loop( ){
  char key = kpd.getKey();
  lcd_keypad();
  // read the state of the faultpin value:
buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);
buttonState4 = digitalRead(buttonPin4);
buttonState5 = digitalRead(buttonPin5);
 int restore_msg(int hr);
  if (key == '*')
  {
    flg=0;
    flu=0;
    lcd.clear();
    delay(500);
    lcd.print("Press A- Display");
    lcd.setCursor(0,1);
    lcd.print("C - Check Faults");
     delay(2000);
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
      delay(5000);
      restore_msg(5);
      lcd.clear();
      lcd.print("  MSG SENT\x1A");
      Serial.print("MSG SENT\n");
      delay(5000);
      flu=1;
      lcd_keypad();
     
    }
  else
  {
   lcd_keypad();
   lcd.clear();
   lcd.print("fault Still exists");
   Serial.print("fault Still exists");
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
if (flg == 1){
fault_display();
 delay(500);}
 if (flu == 1)
 { fault_detect();
  delay(500);
 }
 
  
  

}
