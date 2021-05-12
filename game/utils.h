#define LEFT_BUTTON (byte) 2
#define MIDDLE_BUTTON (byte) 3
#define RIGHT_BUTTON (byte) 4

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

#ifndef HEADERFILE_LCD_UTILS
#include "LCD_utils.h"
#endif

byte first_platform = 15;
byte last_platform = 17;

byte ball_x = first_platform + BALL_PLATFORM_INIT_POS;
byte ball_y = PIXEL_DISPLAY_LEN - 2;
byte ball_h_direct = RIGHT;
byte ball_v_direct = UP;

byte obstacles[OBSTACL_H][OBSTACL_W] {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void move_platform(byte direction);
void activate_buttons();
void move_ball();

void activate_buttons() {
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    // pinMode(MIDDLE_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
}

void move_platform(byte direction) {
    byte old_platform;
    if (direction == LEFT && first_platform != 0) {
        old_platform = last_platform;
        first_platform--;
        last_platform--;
        update_platform(direction, old_platform);
    } else if (direction == RIGHT && last_platform != 31) {
        old_platform = first_platform;
        first_platform++;
        last_platform++;
        update_platform(direction, old_platform);
    }
}

void collide_with_obstacle(byte x, byte y) {
}

void move_ball() {
    byte old_x = ball_x;
    byte old_y = ball_y;
    if(ball_v_direct == UP) {
        if(ball_h_direct == RIGHT) {
            if(ball_x < RIGHT_PIXEL_BORDER - 1 && ball_y > UP_PIXEL_BORDER) {
                ball_x++;
                ball_y--;
            } else {
                if(ball_x >= RIGHT_PIXEL_BORDER - 1) {
                    ball_h_direct = LEFT;
                }
                if(ball_y <= UP_PIXEL_BORDER) {
                    ball_v_direct = DOWN;
                }
            }
        } else if(ball_h_direct == LEFT) {
            if(ball_x > LEFT_PIXEL_BORDER && ball_y > UP_PIXEL_BORDER) {
                ball_x--;
                ball_y--;
            } else {
                if(ball_x <= LEFT_PIXEL_BORDER) {
                    ball_h_direct = RIGHT;
                }
                if(ball_y <= UP_PIXEL_BORDER) {
                    ball_v_direct = DOWN;
                }
            }
        }
    }

    if(ball_v_direct == DOWN) {
        if(ball_h_direct == RIGHT) {
            if(ball_x < RIGHT_PIXEL_BORDER - 1 && ball_y < DOWN_PIXEL_BORDER) {
                ball_x++;
                ball_y++;
            } else {
                if(ball_x >= RIGHT_PIXEL_BORDER - 1) {
                    ball_h_direct = LEFT;
                }
                if(ball_y >=  DOWN_PIXEL_BORDER) {
                    ball_v_direct = UP;
                }
            }
        }
        if(ball_h_direct == LEFT) {
            if(ball_x > LEFT_PIXEL_BORDER && ball_y < DOWN_PIXEL_BORDER) {
                ball_x--;
                ball_y++;
            } else {
                if(ball_x <= LEFT_PIXEL_BORDER) {
                    ball_h_direct = RIGHT;
                }
                if(ball_y >=  DOWN_PIXEL_BORDER) {
                    ball_v_direct = UP;
                }
            }
        }
    }

    draw_ball(old_x, old_y, ball_x, ball_y);
}
