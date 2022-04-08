#include <Keypad_I2C.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>
const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {0,1,2,3}; 
byte colPins[COLS] = {4,5,6,7};

int i2caddress = 0x38;

Keypad_I2C kpd = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, i2caddress );

void setup(){
  Serial.begin(9600);
  kpd.begin();
}

void loop(){
  char key = kpd.getKey();
  if (key){
    Serial.println(key);
  }
}
