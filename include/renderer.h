#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <Arduino.h>

#include "config.h"

#define DISP_WIDTH 640
#define DISP_HEIGHT 384

#ifdef DISP_3C
#include <GxEPD2_3C.h>
extern GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 4> display;
#endif

typedef enum alignment {
    LEFT,
    RIGHT,
    CENTER
} alignment_t;

uint16_t getStringWidth(String text);
uint16_t getStringHeight(String text);
void drawString(int16_t x, int16_t y, String text, alignment_t alignment,
                uint16_t color = GxEPD_BLACK);
void drawMultiLnString(int16_t x, int16_t y, String text, alignment_t alignment,
                       uint16_t max_width, uint16_t max_lines,
                       int16_t line_spacing, uint16_t color = GxEPD_BLACK);
void initDisplay();
// void drawStatusBar(String statusStr, String refreshTimeStr, int rssi,
//                    double batVoltage);
// void drawError(const uint8_t *bitmap_196x196,
//                const String &errMsgLn1, const String &errMsgLn2);

#endif