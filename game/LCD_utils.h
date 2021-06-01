#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#define HEADERFILE_LCD_UTILS

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

#define BACKGROUND_COLOR ST77XX_BLACK

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

void print_text(byte x_pos, byte y_pos, char *text, byte text_size, uint16_t color);
void update_platform(byte direction, byte old_platform);
void draw_ball(byte old_x, byte old_y, byte x, byte y);
void paint_over_obstacle(uint8_t x, uint8_t y);
uint16_t get_uint16_color(uint8_t color);


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

void draw_ball(byte old_x, byte old_y, byte x, byte y) {
    tft.fillRect(old_x * PIXEL, old_y * PIXEL, PIXEL, PIXEL, ST77XX_BLACK);
    tft.fillRect(x * PIXEL, y * PIXEL, PIXEL, PIXEL, ST77XX_WHITE);
}

void paint_over_obstacle(uint8_t x, uint8_t y) {
    tft.fillRect(
                    x * 2 * PIXEL, /* x */
                    y * PIXEL + PIXEL * OBSTACL_START, /* y */
                    PIXEL * 2, /* width */
                    PIXEL, /* hight */
                    BACKGROUND_COLOR);
}

uint16_t get_uint16_color(uint8_t color) {
    switch (color) {
    case BYTE_BLACK:
        return ST77XX_BLACK;
        break;
    case BYTE_WHITE:
        return ST77XX_WHITE;
        break;
    case BYTE_RED:
        return ST77XX_RED;
        break;
    case BYTE_GREEN:
        return ST77XX_GREEN;
        break;
    case BYTE_BLUE:
        return ST77XX_BLUE;
        break;
    case BYTE_CYAN:
        return ST77XX_CYAN;
        break;
    case BYTE_MAGENTA:
        return ST77XX_MAGENTA;
        break;
    case BYTE_YELLOW:
        return ST77XX_YELLOW;
        break;
    case BYTE_ORANGE:
        return ST77XX_ORANGE;
        break;
    
    default:
        return NO_COLOR;
    }
}
