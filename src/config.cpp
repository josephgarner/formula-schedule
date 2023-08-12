#include "config.h"

#include <Arduino.h>

// PINS
// ADC pin used to measure battery voltage
const uint8_t PIN_BAT_ADC = A2;
// Pins for Waveshare e-paper Driver Board
const uint8_t PIN_EPD_BUSY = 13;
const uint8_t PIN_EPD_CS = 2;
const uint8_t PIN_EPD_RST = 21;
const uint8_t PIN_EPD_DC = 22;
const uint8_t PIN_EPD_SCK = 18;
const uint8_t PIN_EPD_MISO = 19;  // 19 Master-In Slave-Out not used, as no data from display
const uint8_t PIN_EPD_MOSI = 23;