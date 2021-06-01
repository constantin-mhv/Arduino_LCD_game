
#define HEADERFILE_CONSTANTS

#define PIXEL (uint8_t) 4

#define BAR_LINE_POS (uint8_t) 11
#define DISPLAY_LEN (uint8_t) 128
#define PIXEL_DISPLAY_LEN (uint8_t) DISPLAY_LEN / PIXEL

#define PLATFORM_H (uint8_t) 1 * PIXEL
#define PLATFORM_W (uint8_t) 4 * PIXEL
#define PLATFORM_N_PARTS (uint8_t) 3

#define BALL_PLATFORM_INIT_POS (uint8_t) 1
#define UP_PIXEL_BORDER (uint8_t) 3
#define DOWN_PIXEL_BORDER (uint8_t) PIXEL_DISPLAY_LEN - 2
#define LEFT_PIXEL_BORDER (uint8_t) 0
#define RIGHT_PIXEL_BORDER (uint8_t) PIXEL_DISPLAY_LEN

#define OBSTACL_H (uint8_t) 16
#define OBSTACL_W (uint8_t) 16
#define OBSTACL_START 4
#define OBSTACL_END 9

#define LEFT (uint8_t) 1
#define RIGHT (uint8_t) 2
#define UP (uint8_t) 1
#define DOWN (uint8_t) 2 


/* --- 8bit colors --- */
#define BYTE_BLACK (uint8_t) 0
#define BYTE_WHITE (uint8_t) 1
#define BYTE_RED (uint8_t) 2
#define BYTE_GREEN (uint8_t) 3
#define BYTE_BLUE (uint8_t) 4
#define BYTE_CYAN (uint8_t) 5
#define BYTE_MAGENTA (uint8_t) 6
#define BYTE_YELLOW (uint8_t) 7
#define BYTE_ORANGE (uint8_t) 8
#define NO_COLOR (uint8_t) 255
#define NO_OBSTACLE NO_COLOR

/* TODO: down pixel border */
