#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

void print_text(byte x_pos, byte y_pos, char *text, byte text_size, uint16_t color);
void update_platform(byte direction, byte old_platform);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void print_text(byte x_pos, byte y_pos, char *text, byte text_size, uint16_t color) {
    tft.setCursor(x_pos, y_pos);
    tft.setTextSize(text_size);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void update_platform(byte direction, byte old_platform) {
    tft.fillRect(old_platform * PIXEL, DISPLAY_LEN - PIXEL, PIXEL,
        PIXEL, ST77XX_BLACK);
    if (direction == LEFT) {
        tft.fillRect((old_platform - PLATFORM_N_PARTS) * PIXEL,
            DISPLAY_LEN - PIXEL, PIXEL, PIXEL, ST77XX_GREEN);
    } else {
        tft.fillRect((old_platform + PLATFORM_N_PARTS) * PIXEL,
            DISPLAY_LEN - PIXEL, PIXEL, PIXEL, ST77XX_GREEN);
    }
}
