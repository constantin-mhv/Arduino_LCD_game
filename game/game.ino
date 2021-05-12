#include "LCD_utils.h"
#include "utils.h"

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

void setup(void) {
    byte i;
    tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
    tft.fillScreen(ST77XX_BLACK);
    tft.setRotation(90); // set display orientation

    activate_buttons();
    tft.drawFastHLine(0, BAR_LINE_POS, 128, 0x7124);
    print_text(0, 1 , " o o o", 1,  ST77XX_RED);
    print_text(80, 1 , "SCORE: ", 1,  ST77XX_WHITE);

    for (i = first_platform; i <= last_platform; i++) {
        tft.fillRect(i * PIXEL, DISPLAY_LEN - PIXEL, PIXEL, PIXEL, ST77XX_GREEN);
    }
}

void loop() {
    if (digitalRead(LEFT_BUTTON) == LOW) {
        move_platform(LEFT);
    }
    if (digitalRead(RIGHT_BUTTON) == LOW) {
        move_platform(RIGHT);
    }

    delay(30);
}
