#include <Arduino.h>
#include <GxEPD2.h>
#include <GxEPD2_3C.h>

#include "config.h"
#include "icons/icons_logos.h"
#include "renderer.h"

#include FONT_HEADER

void setup() {
    unsigned long startTime = millis();
    Serial.begin(115200);
    double batteryVoltage =
        static_cast<double>(analogRead(PIN_BAT_ADC)) / 1000.0 * (3.3 / 2.0);

    Serial.println("Battery voltage: " + String(batteryVoltage, 2));

    initDisplay();
    do {
        display.setFont(&FONT_16pt8b);
        // drawString(10,
        //            54,
        //            "This is a test Message", LEFT);
        // drawString(10,
        //            100,
        //            "This is a second line text message and an", LEFT);
        // display.drawInvertedBitmap(10, 10, F1_640x160,
        //                            640, 160, GxEPD_BLACK);
        // Logo
        display.drawRect(10, 10, 305, 100, GxEPD_BLACK);
        // Weather
        display.drawRect(10, 120, 305, 194, GxEPD_BLACK);
        // Schedule
        display.drawRect(325, 10, 305, 304, GxEPD_BLACK);
        // timeline
        display.drawRect(10, 324, 620, 50, GxEPD_BLACK);
    } while (display.nextPage());
    display.powerOff();

    Serial.println("Finished writing to display");
}

void loop() {
    // put your main code here, to run repeatedly:
}