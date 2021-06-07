#include "LCD_utils.h"
#include "utils.h"
#include "accelerometer_utils.h"
#include "constants.h"

#ifndef HEADERFILE_LEVELS
#include "levels.h"
#endif

void setup(void) {
    tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
    tft.fillScreen(ST77XX_BLACK);
    tft.setRotation(0); // set display orientation

    activate_all();
    tft.drawFastHLine(0, BAR_LINE_POS, 128, 0x7124);
    update_lives(num_lives);
    print_text(65, 1 , "SCORE: 0", 1,  ST77XX_WHITE);

    draw_platform(ST77XX_GREEN);

    /* draw ball */
    tft.fillRect(ball_x * PIXEL, ball_y * PIXEL, PIXEL, PIXEL, ST77XX_WHITE);

    current_level = prepare_current_level(current_level);
    draw_obstacles(current_obstacles);
}

static bool pressed_right_button;
static bool pressed_left_button;

void loop() {
    /* change level */
    if (digitalRead(LEFT_BUTTON) == LOW && !pressed_left_button) {
        tft.fillRect(ball_x * PIXEL, ball_y * PIXEL, PIXEL, PIXEL, ST77XX_BLACK);
        tft.fillRect(0, BAR_LINE_POS + 1, DISPLAY_LEN,
            INIT_LAST_PLATFORM * PIXEL, ST77XX_BLACK);
        reset_ball_platform();
        current_level = prepare_current_level(current_level);
        draw_obstacles(current_obstacles);
        reset_animation();
        pressed_left_button = true;
    } else if (digitalRead(LEFT_BUTTON) == HIGH) {
        pressed_left_button = false;
    }
    /* turn on/off RGB LEDs */
    if (digitalRead(RIGHT_BUTTON) == LOW && !pressed_left_button) {
        if (light_shine) {
            RGB_light(0, 0, 0);
        }
        light_shine = !light_shine;
        pressed_right_button = true;
    } else if (digitalRead(LEFT_BUTTON) == HIGH) {
        pressed_right_button = false;
    }
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

    delay(SPEED);
    digitalWrite(BUZZER_PIN, HIGH);
    // RGB_light(0, 0, 0);
}
