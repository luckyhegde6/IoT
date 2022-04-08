#include <Keypad_I2C.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x38,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
const byte ROWS = 4; 
const byte COLS = 4; 
int flg;   //flag for fault_display 
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
const int buttonPin1 = P1_3;     // the number of the fault input pin
const int buttonPin2 = P1_4;     // the number of the fault input pin
const int buttonPin3 = P1_5;    // the number of the fault input pin
const int buttonPin4 = P2_0;    // the number of the fault input pin
const int buttonPin5 = P2_1;    // the number of the fault input pin
// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
int buttonState4 = 0;         // variable for reading the pushbutton status
int buttonState5 = 0;         // variable for reading the pushbutton status
const int ledPin1 =  RED_LED;      // the number of the LED pin
  
 
void setup()
{
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
  lcd.print("Use keypad");
  lcd.setCursor(0,1);
  lcd.print("Press * to clear");  
 kpd.begin();
}

void loop()
{
  buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);
buttonState4 = digitalRead(buttonPin4);
buttonState5 = digitalRead(buttonPin5);
char key = kpd.getKey();
  
  if (key == '*')
  {
  lcd.clear();
  }
   if (buttonState2 == HIGH) 
  {  digitalWrite(ledPin1, HIGH);
     delay(200);
     digitalWrite(ledPin1, LOW);
      lcd.clear();
     lcd.print("LG Fault");
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
     lcd.print("LLG Fault");
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
     lcd.print("LL Fault");
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
    lcd.print("3-Ph Fault");
   lcd.setCursor(0,1);
  lcd.print("Press * to clear"); 
  }
  else if(buttonState1 == HIGH)
  { lcd.clear();
  lcd.print("NO Fault");
 delay(200);
 lcd.setCursor(0,1);
  lcd.print("Press * to clear");
   } 
 }
