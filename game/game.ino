#include "LCD_utils.h"
#include "utils.h"
#include "accelerometer_utils.h"

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

#ifndef HEADERFILE_LEVELS
#include "levels.h"
#endif


void setup(void) {
    byte i, j;
    tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
    tft.fillScreen(ST77XX_BLACK);
    tft.setRotation(0); // set display orientation

    activate_buttons();
    tft.drawFastHLine(0, BAR_LINE_POS, 128, 0x7124);
    update_lives(num_lives);
    print_text(65, 1 , "SCORE: 0", 1,  ST77XX_WHITE);

    draw_platform(ST77XX_GREEN);

    /* draw ball */
    tft.fillRect(ball_x * PIXEL, ball_y * PIXEL, PIXEL, PIXEL, ST77XX_WHITE);

    prepare_current_level();

    /* draw obstacles */
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

void loop() {
    if (init_platform) {
        if (get_direction(ball_h_direct) == LEFT) {
            move_platform_with_ball(LEFT);
        } else if (get_direction(ball_h_direct) == RIGHT) {
            move_platform_with_ball(RIGHT);
        } else if ( digitalRead(MIDDLE_BUTTON) == LOW) {
            init_platform = false;
        }
    } else {
        move_ball();
        if (get_direction(ball_h_direct) == LEFT) {
            move_platform(LEFT);
        }
        else if (get_direction(ball_h_direct) == RIGHT) {
            move_platform(RIGHT);
        }
    }

    delay(85);
    digitalWrite(BUZZER_PIN, HIGH);
    // RGB_light(0, 0, 0);
}
