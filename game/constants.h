
#define HEADERFILE_CONSTANTS

#define BUZZER_PIN 6

#define PIXEL 4

#define BAR_LINE_POS 11
#define LIVES_W 9
#define BAR_PIXEL_H 2
#define DISPLAY_LEN 128
#define PIXEL_DISPLAY_LEN (DISPLAY_LEN / PIXEL)

#define PLATFORM_H 1 * PIXEL
#define PLATFORM_W 4 * PIXEL
#define PLATFORM_N_PARTS 3

#define BALL_PLATFORM_INIT_POS 1
#define UP_PIXEL_BORDER 3
#define DOWN_PIXEL_BORDER (PIXEL_DISPLAY_LEN - 2)
#define LEFT_PIXEL_BORDER 0
#define RIGHT_PIXEL_BORDER PIXEL_DISPLAY_LEN

#define OBSTACL_H 16
#define OBSTACL_W 16
#define OBSTACL_START 4
#define OBSTACL_END 19

#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2 

#define INIT_FIRST_PLATFORM 15
#define INIT_LAST_PLATFORM 17

#define INIT_BALL_X (INIT_FIRST_PLATFORM + BALL_PLATFORM_INIT_POS)
#define INIT_BALL_Y (PIXEL_DISPLAY_LEN - 2)

#define LIVES 3
#define SCORE_STEP 10
#define SCORE_POS 65

/* --- 8bit colors --- */
#define BYTE_BLACK 9
#define BYTE_WHITE 1
#define BYTE_RED 2
#define BYTE_GREEN 3
#define BYTE_BLUE 4
#define BYTE_CYAN 5
#define BYTE_MAGENTA 6
#define BYTE_YELLOW 7
#define BYTE_ORANGE 8
#define NO_COLOR 0
#define NO_OBSTACLE NO_COLOR

/* --- sounds --- */
#define SOUND_OBSTACLE 220
#define SOUND_PLATFORM 150
#define SOUND_LOSE_LIFE 90

/* TODO: down pixel border */
