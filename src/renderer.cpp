#include "renderer.h"

#include "config.h"

#ifdef DISP_3C
GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 4> display(
    GxEPD2_750c(PIN_EPD_CS,
                PIN_EPD_DC,
                PIN_EPD_RST,
                PIN_EPD_BUSY));
#endif

uint16_t getStringWidth(String text) {
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return w;
}

uint16_t getStringHeight(String text) {
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return h;
}

void drawString(int16_t x, int16_t y, String text, alignment_t alignment, uint16_t color) {
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextColor(color);
    display.getTextBounds(text, x, y, &x1, &y1, &w, &h);
    if (alignment == RIGHT)
        x = x - w;
    if (alignment == CENTER)
        x = x - w / 2;
    display.setCursor(x, y);
    display.print(text);
}

void initDisplay() {
    display.init(115200, true, 2, false);
    SPI.begin(PIN_EPD_SCK,
              PIN_EPD_MISO,
              PIN_EPD_MOSI,
              PIN_EPD_CS);
    display.setRotation(0);
    display.setTextSize(1);
    display.setTextColor(GxEPD_BLACK);
    display.setTextWrap(false);
    display.fillScreen(GxEPD_WHITE);
    display.setFullWindow();
}

/**


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

*/