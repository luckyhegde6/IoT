void setupESP8266()
{
    while (1) {
        Serial.print("restaring esp8266...");
        if (esp8266.restart()) {
            Serial.print("ok\r\n");
            break;
        }
        else {
            Serial.print("not ok...\r\n");
            Serial.print("Trying to kick...");
            while (1) {
                if (esp8266.kick()) {
                    Serial.print("ok\r\n");
                    break;
                }
                else {
                    Serial.print("not ok... Wait 5 sec and retry...\r\n");
                    delay(5000);
                }
            }
        }
    }

    Serial.print("setup begin\r\n");
    Serial.print("FW Version:");
    Serial.println(esp8266.getVersion().c_str());

    while (1) {
        if (esp8266.setOprToStation()) {
            Serial.print("to station ok\r\n");
            break;
        }
        else {
            Serial.print("to station err\r\n");
            Serial.println("Wait 5 seconds and try again...");
            delay(5000);
        }
    }

    while (1) {
        if (esp8266.joinAP(SSID, PASSWORD)) {
            Serial.print("Join AP success\r\n");
            break;
        }
        else {
            Serial.print("Join AP failure\r\n");
            Serial.println("Wait 5 seconds and try again...");
            delay(5000);
        }
    }
    Serial.print("setup end\r\n");
}

void setup() {
 ... // serial setup, etc
 setupESP8266();
}
