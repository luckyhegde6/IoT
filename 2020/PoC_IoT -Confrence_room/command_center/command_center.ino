// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// This example only works with Arduino IDE 1.6.8 or later.

#include <ESP8266WiFi.h>
#include <time.h>
#include "command_center.h"
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>

const char ssid[] = "lucky"; //  your WiFi SSID (name)
const char pass[] = "laxmish53";    // your WiFi password (use for WPA, or use as key for WEP)
const char connectionString[] = "HostName=IoTPoCConferencerRoom.azure-devices.net;DeviceId=nodemcuv1;SharedAccessKey=zkiACBFAF8u3JRc6QhsQ7yXwJqFC0a1aT0NEuV72eDc=";
  
int status = WL_IDLE_STATUS;

///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    initSerial();
    initWifi();
    initTime();

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
    // This function doesn't exit.
    command_center_run();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initSerial() {
    // Start serial and initialize stdout
    Serial.begin(115200);
    Serial.setDebugOutput(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initWifi() {
    // Attempt to connect to Wifi network:
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to wifi");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initTime() {
    time_t epochTime;

    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    while (true) {
        epochTime = time(NULL);

        if (epochTime == 0) {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        } else {
            Serial.print("Fetched NTP epoch time is: ");
            Serial.println(epochTime);
            break;
        }
    }
}

