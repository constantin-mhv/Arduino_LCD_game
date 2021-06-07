#define LEFT_BUTTON 7
#define MIDDLE_BUTTON 4
#define RIGHT_BUTTON 2

#define RED_LIGHT_PIN A3
#define GREEN_LIGHT_PIN A4
#define BLUE_LIGHT_PIN A5

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

#ifndef HEADERFILE_LCD_UTILS
#include "LCD_utils.h"
#endif

#ifndef HEADERFILE_LEVELS
#include "levels.h"
#endif

void activate_all(void);
void move_platform(uint8_t direction);
void move_platform_with_ball(uint8_t direction);
void reset_ball_platform(void);
void lose_life(void);
void collide_obstacle(uint8_t x, uint8_t y);
void move_ball_up_right(void);
void move_ball_up_left(void);
void move_ball_down_left(void);
void move_ball_down_right(void);
void move_ball(void);
void play_sound(uint8_t sound);
void RGB_light(uint8_t red_light_value, uint8_t green_light_value,
    uint8_t blue_light_value);
void change_light(uint8_t x, uint8_t y);

uint8_t first_platform = INIT_FIRST_PLATFORM;
uint8_t last_platform = INIT_LAST_PLATFORM;

uint8_t ball_x = INIT_BALL_X;
uint8_t ball_y = INIT_BALL_Y;
uint8_t ball_h_direct = RIGHT;
uint8_t ball_v_direct = UP;
uint8_t current_level = 1;
uint8_t num_lives = LIVES;
uint16_t score;

bool init_platform = true;
bool light_shine = true;
bool no_lives;

void activate_all(void) {
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(MIDDLE_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);

    pinMode(RED_LIGHT_PIN, OUTPUT);
    pinMode(GREEN_LIGHT_PIN, OUTPUT);
    pinMode(BLUE_LIGHT_PIN, OUTPUT);

    pinMode(BUZZER_PIN, OUTPUT);
}

void move_platform(uint8_t direction) {
    uint8_t old_platform;
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

void move_platform_with_ball(uint8_t direction) {
    uint8_t old_platform;
    if (direction == LEFT && first_platform != 0) {
        old_platform = last_platform;
        first_platform--;
        last_platform--;
        update_platform(direction, old_platform);
        draw_ball(ball_x, ball_y, ball_x - 1, ball_y);
        ball_x--;
    } else if (direction == RIGHT && last_platform != 31) {
        old_platform = first_platform;
        first_platform++;
        last_platform++;
        update_platform(direction, old_platform);
        draw_ball(ball_x, ball_y, ball_x + 1, ball_y);
        ball_x++;
    }
}

void reset_ball_platform(void) {
    first_platform = INIT_FIRST_PLATFORM;
    last_platform = INIT_LAST_PLATFORM;

    ball_x = INIT_BALL_X;
    ball_y = INIT_BALL_Y;
    ball_h_direct = RIGHT;
    ball_v_direct = UP;
    reset_animation();
}

void lose_life(void) {
    uint8_t old_score;

    num_lives--;
    init_platform = true;
    update_lives(num_lives);
    reset_ball_platform();
    if (num_lives == 0) {
        old_score = score;
        score = 0;
        update_score(score);
        delay(WAIT_TIME);
        score = old_score;
        update_score(score);
        delay(WAIT_TIME);
        score = 0;
        update_score(score);
        score = old_score;
        update_score(score);
        delay(WAIT_TIME);
        score = 0;
        update_score(score);

        num_lives = LIVES;
        update_lives(num_lives);
    }
}

void collide_obstacle(uint8_t x, uint8_t y) {
    play_sound(SOUND_OBSTACLE);
    paint_over_obstacle(x, y);
    if (light_shine) {
        change_light(x, y);
    }
    score += SCORE_STEP;
    update_score(score);
}

void move_ball_up_right(void) {
    uint8_t x = ball_x + 1;
    uint8_t y = ball_y - 1;

    if (ball_x + 1 == RIGHT_PIXEL_BORDER) {
        move_ball_up_left();
        return;
    } else if ( ball_y == UP_PIXEL_BORDER) {
        move_ball_down_right();
        return;
    }
    
    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;

     if ((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if ((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        collide_obstacle(obstacle_v_x, obstacle_v_y);
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        move_ball_down_right();
        return;
    } else if (ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_h_x, obstacle_h_y);
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        move_ball_up_left();
        return;
    } else if (y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_diag_x, obstacle_diag_y);
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
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

    if (ball_x  == LEFT_PIXEL_BORDER) {
        move_ball_up_right();
        return;
    } else if (ball_y == UP_PIXEL_BORDER) {
        move_ball_down_left();
        return;
    }

    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;

    if ((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if ((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        collide_obstacle(obstacle_v_x, obstacle_v_y);
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        move_ball_down_left();
        return;
    } else if (ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_h_x, obstacle_h_y);
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        move_ball_up_right();
        return;
    } else if (y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_diag_x, obstacle_diag_y);
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
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

    if (ball_x  == LEFT_PIXEL_BORDER) {
        move_ball_down_right();
        return;
    } else if (ball_y == DOWN_PIXEL_BORDER) {
        if (ball_x + 1< first_platform || ball_x - 1> last_platform) {
            lose_life();
            return;
        }
        play_sound(SOUND_PLATFORM);
        move_ball_up_left();
        return;
    }

    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;
    
    if ((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if ((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        collide_obstacle(obstacle_v_x, obstacle_v_y);
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        move_ball_up_left();
        return;
    } else if (ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_h_x, obstacle_h_y);
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        move_ball_down_right();
        return;
    } else if (y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_diag_x, obstacle_diag_y);
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
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

    if (ball_x + 1 == RIGHT_PIXEL_BORDER) {
        move_ball_down_left();
        return;
    } else if (ball_y == DOWN_PIXEL_BORDER) {
        if (ball_x + 1 < first_platform || ball_x - 1> last_platform) {
            lose_life();
            return;
        }
        play_sound(SOUND_PLATFORM);
        move_ball_up_right();
        return;
    }

    uint8_t obstacle_diag_x = x / 2;
    uint8_t obstacle_diag_y = y  - OBSTACL_START;

    uint8_t obstacle_v_x = ball_x / 2;
    uint8_t obstacle_v_y = y - OBSTACL_START;

    uint8_t obstacle_h_x = x / 2;
    uint8_t obstacle_h_y = ball_y - OBSTACL_START;

    if ((y >= OBSTACL_START) && (y <= OBSTACL_END) &&
            (current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE)) {
        if ((current_obstacles[obstacle_v_y][obstacle_v_x] != NO_OBSTACLE))
        collide_obstacle(obstacle_v_x, obstacle_v_y);
        current_obstacles[obstacle_v_y][obstacle_v_x] = NO_OBSTACLE;
        move_ball_up_right();
        return;
    } else if (ball_y >= OBSTACL_START && ball_y <= OBSTACL_END &&
            current_obstacles[obstacle_h_y][obstacle_h_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_h_x, obstacle_h_y);
        current_obstacles[obstacle_h_y][obstacle_h_x] = NO_OBSTACLE;
        move_ball_down_left();
        return;
    } else if (y >= OBSTACL_START && y <= OBSTACL_END &&
            current_obstacles[obstacle_diag_y][obstacle_diag_x] != NO_OBSTACLE) {
        collide_obstacle(obstacle_diag_x, obstacle_diag_y);
        current_obstacles[obstacle_diag_y][obstacle_diag_x] = NO_OBSTACLE;
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
    if (ball_v_direct == UP && ball_h_direct == RIGHT) {
        move_ball_up_right();
    } else if (ball_v_direct == UP && ball_h_direct == LEFT) {
        move_ball_up_left();
    } else if (ball_v_direct == DOWN && ball_h_direct == RIGHT) {
        move_ball_down_right();
    } else if (ball_v_direct == DOWN && ball_h_direct == LEFT) {
        move_ball_down_left();
    }
}

void play_sound(uint8_t sound) {
    analogWrite(BUZZER_PIN, sound);
}

void RGB_light(uint8_t red_light_value, uint8_t green_light_value,
    uint8_t blue_light_value) {
  analogWrite(RED_LIGHT_PIN, red_light_value);
  analogWrite(GREEN_LIGHT_PIN, green_light_value);
  analogWrite(BLUE_LIGHT_PIN, blue_light_value);
}

void change_light(uint8_t x, uint8_t y) {
    switch (current_obstacles[y][x]) {
    case BYTE_RED:
        RGB_light(255, 0, 0);
        break;
    case BYTE_GREEN:
        RGB_light(0, 255, 0);
        break;
    case BYTE_BLUE:
        RGB_light(0, 0, 255);
        break;
    case BYTE_CYAN:
        RGB_light(0, 255, 255);
        break;
    case BYTE_MAGENTA:
        RGB_light(255, 0, 255);
        break;
    case BYTE_YELLOW:
        RGB_light(255, 255, 0);
        break;
    case BYTE_ORANGE:
        RGB_light(251, 143, 1);
        break;
    }
}
