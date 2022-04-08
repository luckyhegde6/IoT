#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
void setup()   {                
  Serial.begin(9600);
// initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
    // Clear the buffer.
  display.clearDisplay();
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Sensor:");
  display.println(sensorValue);
  display.display();
    delay(100);
    if(sensorValue>500)
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

    }
      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    
  // Clear the buffer.
  display.clearDisplay();
  
}
