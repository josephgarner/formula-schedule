#include <Arduino.h>
#include <GxEPD2.h>
#include <GxEPD2_3C.h>
#include <WiFi.h>

#include "config.h"
#include "icons/icons_logos.h"
#include "network.h"
#include "renderer.h"

#include FONT_HEADER

void setup() {
    unsigned long startTime = millis();
    Serial.begin(115200);
    double batteryVoltage =
        static_cast<double>(analogRead(PIN_BAT_ADC)) / 1000.0 * (3.3 / 2.0);

    Serial.println("Battery voltage: " + String(batteryVoltage, 2));

    int wifiRSSI = 0;
    wl_status_t wifiStatus = startWiFi(wifiRSSI);
}

void loop() {
    // put your main code here, to run repeatedly:
}