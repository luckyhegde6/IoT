#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); // uno sw RX(pin3) --> esp8266 TX, uno sw TX(pin2) --> esp8266 RX
void setup()
{
Serial.begin(9600); //for your print
mySerial.begin(115200);

void loop()
  {
    while (mySerial.available())
    {
        Serial.write(mySerial.read());
    }

    while (Serial.available())
    {
        mySerial.write(Serial.read());
    }
}
