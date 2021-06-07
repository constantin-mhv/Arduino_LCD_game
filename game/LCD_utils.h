#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <string.h>
#include <stdio.h>

#define HEADERFILE_LCD_UTILS

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

#define BACKGROUND_COLOR ST77XX_BLACK

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

void print_text(byte x_pos, byte y_pos, char *text, byte text_size,
    uint16_t color);
void draw_platform(uint16_t color);
void reset_animation(void);
void update_platform(byte direction, byte old_platform);
void draw_ball(byte old_x, byte old_y, byte x, byte y);
void update_score(uint16_t score);
void paint_over_obstacle(uint8_t x, uint8_t y);
void update_lives(uint8_t num_lives);
void draw_obstacles(uint8_t current_obstacles[][OBSTACL_W]);
uint16_t get_uint16_color(uint8_t color);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void print_text(byte x_pos, byte y_pos, char *text, byte text_size,
        uint16_t color) {
    tft.setCursor(x_pos, y_pos);
    tft.setTextSize(text_size);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void draw_platform(uint16_t color) {
    uint8_t i;

    for (i = INIT_FIRST_PLATFORM; i <= INIT_LAST_PLATFORM; i++)
        tft.fillRect(i * PIXEL, DISPLAY_LEN - PIXEL, PIXEL, PIXEL, color);
}

void reset_animation(void) {
    tft.fillRect(0, DISPLAY_LEN - 2 * PIXEL, DISPLAY_LEN, 2 * PIXEL, ST77XX_BLACK);
    tft.fillRect(INIT_BALL_X * PIXEL , INIT_BALL_Y * PIXEL, PIXEL, PIXEL, ST77XX_WHITE);
    for (uint8_t i = 0; i < 4; i++) {
        draw_platform(ST77XX_GREEN);
        analogWrite(BUZZER_PIN, SOUND_LOSE_LIFE);
        delay(200);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(60);
        draw_platform(ST77XX_BLACK);
        analogWrite(BUZZER_PIN, SOUND_LOSE_LIFE);
        delay(200);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(60);
        draw_platform(ST77XX_GREEN);
    }
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

void update_score(uint16_t score) {
    tft.fillRect(SCORE_POS + PIXEL * 9, 0, PIXEL * 15, PIXEL * BAR_PIXEL_H,
    ST7735_BLACK);
    char text[5];
    memset(text, 0, 5);
    sprintf(text, "%u", score);
    print_text(SCORE_POS + PIXEL * 9, 1 , text, 1,  ST77XX_WHITE);
}

void paint_over_obstacle(uint8_t x, uint8_t y) {
    tft.fillRect(
                 x * 2 * PIXEL, /* x */
                 y * PIXEL + PIXEL * OBSTACL_START, /* y */
                 PIXEL * 2, /* width */
                 PIXEL, /* hight */
                 BACKGROUND_COLOR);
}

void update_lives(uint8_t num_lives) {
    uint8_t i;
    char text[LIVES * 2 + 1];
    memset(text, 0, LIVES * 2 + 1);
    for (i = 0; i < num_lives * 2; i+=2) {
        text[i] = 'o';
        text[i + 1] = ' ';
    }
    tft.fillRect( 0, 0, PIXEL * LIVES_W, PIXEL * BAR_PIXEL_H, ST7735_BLACK);
    print_text(0, 1 , text, 1,  ST77XX_RED);
}

void draw_obstacles(uint8_t current_obstacles[][OBSTACL_W]) {
    uint8_t i, j;

    for (i = 0; i < OBSTACL_H; i++) {
        for (j = 0; j < OBSTACL_W; j++) {
            if (current_obstacles[i][j] != NO_COLOR)
                tft.fillRect(
                    j * 2 * PIXEL, /* x */
                    i * PIXEL + PIXEL * OBSTACL_START, /* y */
                    PIXEL * 2, /* width */
                    PIXEL, /* hight */
                    get_uint16_color(current_obstacles[i][j]));
        }
    }
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
