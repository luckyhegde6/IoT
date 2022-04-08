int led = 5;
int dataFromBt;
boolean lightBlink = false;

#include "SimpleBLE.h"
SimpleBLE ble;

void onButton(){
    String out = "BLE32 at: ";
    out += String(millis() / 1000);
    Serial.println(out);
    ble.begin(out);
}
void setup()
{  Serial.begin(115200);  // Begin the serial monitor at 9600bps
    Serial.setDebugOutput(true);
    pinMode(0, INPUT_PULLUP);
    Serial.print("ESP32 SDK: ");
    Serial.println(ESP.getSdkVersion());
    ble.begin("ESP32 SimpleBLE");
    Serial.println("Press the button to change the device name");
  ble.begin("$");  // Print three times individually
  ble.begin("$");
  ble.begin("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  pinMode(led, OUTPUT);
}

void loop()
{
 static uint8_t lastPinState = 1;
    uint8_t pinState = digitalRead(0);
    if(!pinState && lastPinState){
        onButton();
    }
    lastPinState = pinState;
    while(Serial.available()) Serial.write(Serial.read());
  if (Serial.available()) // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
 
    Serial.println((char)Serial.read());
    dataFromBt = Serial.read();
 
    //Serial.println(dataFromBt);
    if (dataFromBt == '1') {
      Serial.println("led on");
      digitalWrite(led, HIGH);
      ble.begin("1");
    }
    if (dataFromBt == '0') {
      Serial.println("led off");
      digitalWrite(led, LOW);
      ble.begin("0");
    }
    if (dataFromBt == 'b') {
      Serial.println("a");
      lightBlink = true;
    } else {
      lightBlink = false;
    }
 
  }
 
  if (Serial.available()) // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    //String myStr = (String)Serial.read();
    //char myStr1[] = "hello this is testing!";
 
   // uint8_t payload[myStr.length() + 1];
    //    myStr.getBytes(payload, myStr.length()+1);
 
    int bytes=Serial.available();
    //Serial.readBytes(buffer, startPosition, bytes);
 
    Serial.begin((char)Serial.read());
 
  }
 
  // and loop forever and ever!
  if (lightBlink) 
  {
    digitalWrite(led, HIGH);
    ble.begin("1");
    Serial.println("HIGH");
    delay(500);
    digitalWrite(led, LOW);
    ble.begin("0");
    Serial.println("LOW");
    delay(500);
  }
}
