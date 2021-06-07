#define HEADERFILE_LEVELS

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif
 
uint8_t current_obstacles[OBSTACL_H][OBSTACL_W];

uint8_t level1[OBSTACL_H][OBSTACL_W] {
/* 0 */
    {BYTE_RED, BYTE_RED, BYTE_RED, NO_COLOR,
    BYTE_GREEN, BYTE_GREEN, BYTE_GREEN, NO_COLOR,
    BYTE_ORANGE, BYTE_ORANGE, NO_COLOR, NO_COLOR,
    BYTE_MAGENTA, NO_COLOR, BYTE_MAGENTA, NO_COLOR},
/* 1 */
    {BYTE_RED, NO_COLOR, BYTE_RED, NO_COLOR,
    BYTE_GREEN, NO_COLOR, BYTE_GREEN, NO_COLOR,
    BYTE_ORANGE, NO_COLOR, BYTE_ORANGE, NO_COLOR,
    BYTE_MAGENTA, NO_COLOR, BYTE_MAGENTA, NO_COLOR},
/* 2 */
    {BYTE_RED, BYTE_RED, BYTE_RED, NO_COLOR,
    BYTE_GREEN, BYTE_GREEN, BYTE_GREEN, NO_COLOR,
    BYTE_ORANGE, NO_COLOR, BYTE_ORANGE, NO_COLOR,
    BYTE_MAGENTA, NO_COLOR, BYTE_MAGENTA, NO_COLOR},
/* 3 */
    {BYTE_RED, NO_COLOR, BYTE_RED, NO_COLOR,
    BYTE_GREEN, BYTE_GREEN, NO_COLOR, NO_COLOR,
    BYTE_ORANGE, NO_COLOR, BYTE_ORANGE, NO_COLOR,
    BYTE_MAGENTA, NO_COLOR, BYTE_MAGENTA, NO_COLOR},
/* 4 */
    {BYTE_RED, NO_COLOR, BYTE_RED, NO_COLOR,
    BYTE_GREEN, NO_COLOR, BYTE_GREEN, NO_COLOR,
    BYTE_ORANGE, BYTE_ORANGE, NO_COLOR, NO_COLOR,
    BYTE_MAGENTA, BYTE_MAGENTA, BYTE_MAGENTA, NO_COLOR},
/* 5 */
    {NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR},
/* 6 */
    {NO_COLOR, NO_COLOR, BYTE_CYAN, BYTE_CYAN,
    BYTE_CYAN, NO_COLOR, BYTE_BLUE, BYTE_BLUE,
    NO_COLOR, BYTE_BLUE, NO_COLOR, BYTE_YELLOW,
    BYTE_YELLOW, BYTE_YELLOW, NO_COLOR, NO_COLOR},
/* 7 */
    {NO_COLOR, NO_COLOR, NO_COLOR, BYTE_CYAN,
    NO_COLOR, NO_COLOR, BYTE_BLUE, BYTE_BLUE,
    NO_COLOR, BYTE_BLUE, NO_COLOR, BYTE_YELLOW,
    NO_COLOR, BYTE_YELLOW, NO_COLOR, NO_COLOR},
/* 8 */
    {NO_COLOR, NO_COLOR, NO_COLOR, BYTE_CYAN,
    NO_COLOR, NO_COLOR, BYTE_BLUE, NO_COLOR,
    BYTE_BLUE, BYTE_BLUE, NO_COLOR, BYTE_YELLOW,
    NO_COLOR, BYTE_YELLOW, NO_COLOR, NO_COLOR},
/* 9 */
    {NO_COLOR, NO_COLOR, NO_COLOR, BYTE_CYAN,
    NO_COLOR, NO_COLOR, BYTE_BLUE, NO_COLOR,
    NO_COLOR, BYTE_BLUE, NO_COLOR, BYTE_YELLOW,
    NO_COLOR, BYTE_YELLOW, NO_COLOR, NO_COLOR},
/* 10 */
    {NO_COLOR, NO_COLOR, BYTE_CYAN, BYTE_CYAN,
    BYTE_CYAN, NO_COLOR, BYTE_BLUE, NO_COLOR,
    NO_COLOR, BYTE_BLUE, NO_COLOR, BYTE_YELLOW,
    BYTE_YELLOW, BYTE_YELLOW, NO_COLOR, NO_COLOR}
};


void get_level1(void) {
    uint8_t i;

    for (i = 0; i < OBSTACL_H; i++) {
        memset(current_obstacles[i], NO_COLOR, OBSTACL_W);
        memcpy(current_obstacles[i], level1[i], OBSTACL_W);
    }
}

void get_level2(void) {
    uint8_t i;
    uint8_t line[16] =
        {BYTE_RED, NO_COLOR, BYTE_YELLOW, NO_COLOR,
        BYTE_GREEN, NO_COLOR, BYTE_MAGENTA, NO_COLOR,
        BYTE_ORANGE, NO_COLOR, BYTE_BLUE, NO_COLOR,
        BYTE_CYAN, NO_COLOR, BYTE_WHITE, NO_COLOR};

    for (i = 0; i < OBSTACL_H; i++) {
        memset(current_obstacles[i], NO_COLOR, OBSTACL_W);
    }
    
    for (i = 0; i < OBSTACL_H; i++) {
        memcpy(current_obstacles[i], line, OBSTACL_W);
    }
}

void get_level3(void) {
    uint8_t i;
    for (i = 0; i < OBSTACL_H; i++) {
        memset(current_obstacles[i], NO_COLOR, OBSTACL_W);
    }
    memset(current_obstacles[0], BYTE_BLUE, OBSTACL_H);
    memset(current_obstacles[1], BYTE_BLUE, OBSTACL_H);

    memset(current_obstacles[3], BYTE_YELLOW, OBSTACL_H);
    memset(current_obstacles[4], BYTE_YELLOW, OBSTACL_H);

    memset(current_obstacles[6], BYTE_GREEN, OBSTACL_H);
    memset(current_obstacles[7], BYTE_GREEN, OBSTACL_H);

    memset(current_obstacles[9], BYTE_MAGENTA, OBSTACL_H);
    memset(current_obstacles[10], BYTE_MAGENTA, OBSTACL_H);

    memset(current_obstacles[12], BYTE_CYAN, OBSTACL_H);
    memset(current_obstacles[13], BYTE_CYAN, OBSTACL_H);
}


uint8_t prepare_current_level(uint8_t current_level) {
    if (current_level == 1) {
        get_level1();
        return ++current_level;
    } else if (current_level == 2) {
        get_level2();
        return ++current_level;
    } else if (current_level == 3) {
        get_level3();
        return current_level = 1;
    }
}
