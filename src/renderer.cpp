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

void drawMultiLnString(int16_t x, int16_t y, String text, alignment_t alignment,
                       uint16_t max_width, uint16_t max_lines,
                       int16_t line_spacing, uint16_t color) {
    uint16_t current_line = 0;
    String textRemaining = text;
    // print until we reach max_lines or no more text remains
    while (current_line < max_lines && !textRemaining.isEmpty()) {
        int16_t x1, y1;
        uint16_t w, h;

        display.getTextBounds(textRemaining, 0, 0, &x1, &y1, &w, &h);

        int endIndex = textRemaining.length();
        // check if remaining text is to wide, if it is then print what we can
        String subStr = textRemaining;
        int splitAt = 0;
        int keepLastChar = 0;
        while (w > max_width && splitAt != -1) {
            if (keepLastChar) {
                // if we kept the last character during the last iteration of this while
                // loop, remove it now so we don't get stuck in an infinite loop.
                subStr.remove(subStr.length() - 1);
            }

            // find the last place in the string that we can break it.
            if (current_line < max_lines - 1) {
                splitAt = max(subStr.lastIndexOf(" "),
                              subStr.lastIndexOf("-"));
            } else {
                // this is the last line, only break at spaces so we can add ellipsis
                splitAt = subStr.lastIndexOf(" ");
            }

            // if splitAt == -1 then there is an unbroken set of characters that is
            // longer than max_width. Otherwise if splitAt != -1 then we can continue
            // the loop until the string is <= max_width
            if (splitAt != -1) {
                endIndex = splitAt;
                subStr = subStr.substring(0, endIndex + 1);

                char lastChar = subStr.charAt(endIndex);
                if (lastChar == ' ') {
                    // remove this char now so it is not counted towards line width
                    keepLastChar = 0;
                    subStr.remove(endIndex);
                    --endIndex;
                } else if (lastChar == '-') {
                    // this char will be printed on this line and removed next iteration
                    keepLastChar = 1;
                }

                if (current_line < max_lines - 1) {
                    // this is not the last line
                    display.getTextBounds(subStr, 0, 0, &x1, &y1, &w, &h);
                } else {
                    // this is the last line, we need to make sure there is space for
                    // ellipsis
                    display.getTextBounds(subStr + "...", 0, 0, &x1, &y1, &w, &h);
                    if (w <= max_width) {
                        // ellipsis fit, add them to subStr
                        subStr = subStr + "...";
                    }
                }

            }  // end if (splitAt != -1)
        }      // end inner while

        drawString(x, y + (current_line * line_spacing), subStr, alignment, color);

        // update textRemaining to no longer include what was printed
        // +1 for exclusive bounds, +1 to get passed space/dash
        textRemaining = textRemaining.substring(endIndex + 2 - keepLastChar);

        ++current_line;
    }  // end outer while

    return;
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

// void drawStatusBar(String statusStr, String refreshTimeStr, int rssi,
//                    double batVoltage) {
//     String dataStr;
//     uint16_t dataColor = GxEPD_BLACK;
//     display.setFont(&FONT_6pt8b);
//     int pos = DISP_WIDTH - 2;
//     const int sp = 2;

//     // battery
//     int batPercent = calcBatPercent(batVoltage);
//     if (batVoltage < BATTERY_WARN_VOLTAGE) {
//         dataColor = ACCENT_COLOR;
//     }
//     dataStr = String(batPercent) + "% (" + String(round(100.0 * batVoltage) / 100.0, 2) + "v)";
//     drawString(pos, DISP_HEIGHT - 1 - 2, dataStr, RIGHT, dataColor);
//     pos -= getStringWidth(dataStr) + 25;
//     display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 17,
//                                getBatBitmap24(batPercent), 24, 24, dataColor);
//     pos -= sp + 9;

//     // WiFi
//     dataStr = String(getWiFidesc(rssi));
//     dataColor = rssi >= -70 ? GxEPD_BLACK : ACCENT_COLOR;
//     if (rssi != 0) {
//         dataStr += " (" + String(rssi) + "dBm)";
//     }
//     drawString(pos, DISP_HEIGHT - 1 - 2, dataStr, RIGHT, dataColor);
//     pos -= getStringWidth(dataStr) + 19;
//     display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 13, getWiFiBitmap16(rssi),
//                                16, 16, dataColor);
//     pos -= sp + 8;

//     // last refresh
//     dataColor = GxEPD_BLACK;
//     drawString(pos, DISP_HEIGHT - 1 - 2, refreshTimeStr, RIGHT, dataColor);
//     pos -= getStringWidth(refreshTimeStr) + 25;
// display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 21, wi_refresh_32x32,
//                            32, 32, dataColor);
//     pos -= sp;

//     // status
//     dataColor = ACCENT_COLOR;
//     if (!statusStr.isEmpty()) {
//         drawString(pos, DISP_HEIGHT - 1 - 2, statusStr, RIGHT, dataColor);
//         pos -= getStringWidth(statusStr) + 24;
//         display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 18, error_icon_24x24,
//                                    24, 24, dataColor);
//     }

//     return;
// }

// void drawError(const uint8_t *bitmap_196x196,
//                const String &errMsgLn1, const String &errMsgLn2) {
//     display.setFont(&FONT_26pt8b);
// drawString(DISP_WIDTH / 2,
//            DISP_HEIGHT / 2 + 196 / 2 + 21,
//            errMsgLn1, CENTER);
//     drawString(DISP_WIDTH / 2,
//                DISP_HEIGHT / 2 + 196 / 2 + 76,
//                errMsgLn2, CENTER);
//     display.drawInvertedBitmap(DISP_WIDTH / 2 - 196 / 2,
//                                DISP_HEIGHT / 2 - 196 / 2 - 21,
//                                bitmap_196x196, 196, 196, ACCENT_COLOR);
//     return;
// }