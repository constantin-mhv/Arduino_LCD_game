#define LEFT_BUTTON (byte) 7
#define MIDDLE_BUTTON (byte) 2
#define RIGHT_BUTTON (byte) 4

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

#ifndef HEADERFILE_LCD_UTILS
#include "LCD_utils.h"
#endif

#ifndef HEADERFILE_LEVELS
#include "levels.h"
#endif

uint8_t first_platform = 15;
uint8_t last_platform = 17;

uint8_t ball_x = first_platform + BALL_PLATFORM_INIT_POS;
uint8_t ball_y = PIXEL_DISPLAY_LEN - 2;
uint8_t ball_h_direct = RIGHT;
uint8_t ball_v_direct = UP;

void move_platform(byte direction);
void activate_buttons();
bool collide_with_obstacle(uint8_t x, uint8_t y);
void move_ball_up_right(void);
void move_ball_up_left(void);
void move_ball_down_left(void);
void move_ball_down_right(void);
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

bool collide_with_obstacle(uint8_t x, uint8_t y) {
    uint8_t obstacle_x = x / 2;
    uint8_t obstacle_y = y  - OBSTACL_START;
    if(current_obstacles[obstacle_y][obstacle_x] != NO_OBSTACLE) {
        current_obstacles[obstacle_y][obstacle_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_x, obstacle_y);
        return true;
    }
    return false;
}

bool collide_with_obstacle_h(uint8_t x, uint8_t y) {
    uint8_t obstacle_x = x / 2;
    uint8_t obstacle_y = y  - OBSTACL_START;
    if(current_obstacles[obstacle_y][obstacle_x] != NO_OBSTACLE) {
            current_obstacles[obstacle_y][obstacle_x] = NO_OBSTACLE;
            paint_over_obstacle(obstacle_x, obstacle_y);
            return true;
        }
    return false;
}


void move_ball_up_right(void) {
    uint8_t x = ball_x + 1;
    uint8_t y = ball_y - 1;

    if(ball_x + 1 == RIGHT_PIXEL_BORDER) {
        move_ball_up_left();
        return;
    } else if( ball_y == UP_PIXEL_BORDER) {
        move_ball_down_right();
        return;
    }
    
    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;

     if((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_v_x, obstacle_v_y);
        move_ball_down_right();
        return;
    } else if(ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_h_x, obstacle_h_y);
        move_ball_up_left();
        return;
    } else if(y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        Serial.println("diag");
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_diag_x, obstacle_diag_y);
        move_ball_down_left();
        return;
    }

    draw_ball(ball_x++, ball_y--, x, y);
    ball_v_direct = UP;
    ball_h_direct = RIGHT;
    return;
}

void move_ball_up_left(void) {
    uint8_t x = ball_x - 1;
    uint8_t y = ball_y - 1;

    if(ball_x  == LEFT_PIXEL_BORDER) {
        move_ball_up_right();
        return;
    } else if(ball_y == UP_PIXEL_BORDER) {
        move_ball_down_left();
        return;
    }

    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;

    if((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_v_x, obstacle_v_y);
        move_ball_down_left();
        return;
    } else if(ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_h_x, obstacle_h_y);
        move_ball_up_right();
        return;
    } else if(y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        Serial.println("diag");
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_diag_x, obstacle_diag_y);
        move_ball_down_right();
        return;
    }

    draw_ball(ball_x--, ball_y--, x, y);
    ball_v_direct = UP;
    ball_h_direct = LEFT;
    return;
}

void move_ball_down_left(void) {
    uint8_t x = ball_x - 1;
    uint8_t y = ball_y + 1;

    if(ball_x  == LEFT_PIXEL_BORDER) {
        move_ball_down_right();
        return;
    } else if(ball_y == DOWN_PIXEL_BORDER) {
        move_ball_up_left();
        return;
    }

    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;
    
    if((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_v_x, obstacle_v_y);
        move_ball_up_left();
        return;
    } else if(ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_h_x, obstacle_h_y);
        move_ball_down_right();
        return;
    } else if(y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        Serial.println("diag");
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_diag_x, obstacle_diag_y);
        move_ball_up_right();
        return;
    }

    draw_ball(ball_x--, ball_y++, x, y);
    ball_v_direct = DOWN;
    ball_h_direct = LEFT;
    return;
}

void move_ball_down_right(void) {
    uint8_t x = ball_x + 1;
    uint8_t y = ball_y + 1;

    if(ball_x + 1 == RIGHT_PIXEL_BORDER) {
        move_ball_down_left();
        return;
    } else if(ball_y == DOWN_PIXEL_BORDER) {
        move_ball_up_right();
        return;
    }

    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;

    if((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_v_x, obstacle_v_y);
        move_ball_up_right();
        return;
    } else if(ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_h_x, obstacle_h_y);
        move_ball_down_left();
        return;
    } else if(y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        Serial.println("diag");
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
        paint_over_obstacle(obstacle_diag_x, obstacle_diag_y);
        move_ball_up_left();
        return;
    }
    
    draw_ball(ball_x++, ball_y++, x, y);
    ball_v_direct = DOWN;
    ball_h_direct = RIGHT;
    return;
}

void move_ball(void) {
    bool res;
    if(ball_v_direct == UP && ball_h_direct == RIGHT) {
        move_ball_up_right();
    } else if(ball_v_direct == UP && ball_h_direct == LEFT) {
        move_ball_up_left();
    } else if(ball_v_direct == DOWN && ball_h_direct == RIGHT) {
        move_ball_down_right();
    } else if(ball_v_direct == DOWN && ball_h_direct == LEFT) {
        move_ball_down_left();
    }
}
