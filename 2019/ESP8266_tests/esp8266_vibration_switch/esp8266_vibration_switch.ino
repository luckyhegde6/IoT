/*
 * Vibration switch demo for ESP8266
 *
 * Blink the LED and print debug info when the 
 * switch makes/breaks contact.
 * 
 * The switch is connected between GPIO#2 and GND. The
 * switch is open when still and closes briefly when 
 * shocked/vibrated. In fact, it closes and opens
 * many times very quickly.
 *
 * See http://adafru.it/1766 for a description and
 * a picture of the inside of the switch.
 */

// GPIO#2 has a vibration switch connected to it.
const int vibrationSwitch = 2;
// Adafruit ESP8266 HUZZAH board has an LED on GPIO#0
const int LED = 1;

void setup()
{
    // initialize serial communication
    Serial.begin(115200);
    // make the switch's pin an input with pullup
    pinMode(vibrationSwitch, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
}

void loop()
{
    // Print a line when the switch changes from open to closed 
    // and closed to open.
    // Also print the number of microseconds since the last change.
    static int lastSwitchState = -1;
    static unsigned long lastMicros = 0;
    unsigned long nowMicros;
    // read the switch pin
    int switchState = digitalRead(vibrationSwitch);
    if (lastSwitchState != switchState) {
        // switch changed so print
        nowMicros = micros();
        // micros() rolls over after about 1 hour but this is not a
        // problem for this short test program.
        Serial.print(nowMicros - lastMicros);
        Serial.print(" usecs ");
        Serial.println(switchState ? "open" : "closed");
        lastSwitchState = switchState;
        lastMicros = nowMicros;
        // Change the LED
        digitalWrite(LED, switchState);
    }
}
