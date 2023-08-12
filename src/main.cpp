#include <Arduino.h>
#include <GxEPD2.h>
#include <GxEPD2_3C.h>

#include "config.h"
#include "icons/icons_96x96.h"
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
        drawString(10,
                   54,
                   "This is a test Message", LEFT);
        drawString(10,
                   100,
                   "This is a second line text message and an", LEFT);
        display.drawInvertedBitmap(100, 200, wi_smog_96x96,
                                   96, 96, GxEPD_RED);
    } while (display.nextPage());
    display.powerOff();

    Serial.println("Finished writing to display");
}

void loop() {
    // put your main code here, to run repeatedly:
}