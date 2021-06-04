#define HEADERFILE_LEVELS

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif
 
uint8_t current_level = 0;
uint8_t current_obstacles[OBSTACL_H][OBSTACL_W];
 
uint8_t obstacles1[OBSTACL_H][OBSTACL_W] {
    /* 0 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, BYTE_CYAN, BYTE_RED},
    /* 1 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, BYTE_CYAN, BYTE_RED},
    /* 2 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, BYTE_CYAN, BYTE_RED},
    /* 3 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, BYTE_CYAN, BYTE_RED},
    /* 4 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, BYTE_CYAN, BYTE_RED},
    /* 5 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, BYTE_CYAN, BYTE_RED}
};

uint8_t obstacles2[OBSTACL_H][OBSTACL_W] {
    /* 0 */
    {NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR},
    /* 1 */
    {NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR},
    /* 2 */
    {NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR},
    /* 3 */
    {NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR,
    NO_COLOR, NO_COLOR, NO_COLOR, NO_COLOR},
    /* 4 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, NO_COLOR, NO_COLOR},
    /* 5 */
    {BYTE_RED, BYTE_RED, BYTE_RED, BYTE_RED,
    BYTE_RED, BYTE_RED, BYTE_RED, BYTE_GREEN,
    BYTE_GREEN, NO_COLOR, BYTE_YELLOW, BYTE_ORANGE,
    BYTE_ORANGE, BYTE_GREEN, NO_COLOR, NO_COLOR}
};

void generate_level1() {
    int i, j;

    for(i = 0; i < 8; i++) {
        for (j = 0; j < OBSTACL_W; j++) {
            current_obstacles[i][j] = NO_COLOR;
        }
    }

    for(i = 8; i < OBSTACL_H; i++) {
        for (j = 0; j < OBSTACL_W; j++) {
            if(j < 10)
                current_obstacles[i][j] = 4;   
            else  
                current_obstacles[i][j] = NO_COLOR;        
        }
    }
}

void prepare_current_level() {
    int i;
    // generate_level1();
    
    for(i = 0; i < OBSTACL_H; i++) {
        memcpy(current_obstacles[i], obstacles1[i], OBSTACL_W);
    }
}
