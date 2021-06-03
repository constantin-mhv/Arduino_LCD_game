#include "LCD_utils.h"
#include "utils.h"

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

#ifndef HEADERFILE_LEVELS
#include "levels.h"
#endif

void setup(void) {
    Serial.begin(1200);
    byte i, j;
    tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
    tft.fillScreen(ST77XX_BLACK);
    tft.setRotation(0); // set display orientation

    activate_buttons();
    tft.drawFastHLine(0, BAR_LINE_POS, 128, 0x7124);
    print_text(0, 1 , " o o o", 1,  ST77XX_RED);
    print_text(65, 1 , "SCORE: ", 1,  ST77XX_WHITE);

    /* draw platform */
    for (i = first_platform; i <= last_platform; i++)
        tft.fillRect(i * PIXEL, DISPLAY_LEN - PIXEL, PIXEL, PIXEL, ST77XX_GREEN);

    /* draw ball */
    tft.fillRect(ball_x * PIXEL, ball_y * PIXEL, PIXEL, PIXEL, ST77XX_WHITE);

    /* copy obstalces for current level */
    // for(i = 0; i < OBSTACL_H; i++) {
    //     memcpy(current_obstacles[i], obstacles[i], OBSTACL_W);
    // }
    prepare_current_level();

    /* draw obstacles */
    for(i = 0; i < OBSTACL_H; i++) {
        for(j = 0; j < OBSTACL_W; j++) {
            if(current_obstacles[i][j] != NO_COLOR)
                tft.fillRect(
                    j * 2 * PIXEL, /* x */
                    i * PIXEL + PIXEL * OBSTACL_START, /* y */
                    PIXEL * 2, /* width */
                    PIXEL, /* hight */
                    get_uint16_color(current_obstacles[i][j]));
        }
    }
}

void loop() {
    move_ball();
    if (digitalRead(LEFT_BUTTON) == LOW) {
        move_platform(LEFT);
    }
    if (digitalRead(RIGHT_BUTTON) == LOW) {
        move_platform(RIGHT);
    }

    delay(50);
}
