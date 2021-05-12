
#define HEADERFILE_CONSTANTS

#define PIXEL (byte) 4

#define BAR_LINE_POS (byte) 11
#define DISPLAY_LEN (byte) 128
#define PIXEL_DISPLAY_LEN (byte) DISPLAY_LEN / PIXEL

#define PLATFORM_H (byte) 1 * PIXEL
#define PLATFORM_W (byte) 4 * PIXEL
#define PLATFORM_N_PARTS (byte) 3

#define BALL_PLATFORM_INIT_POS (byte) 1
#define UP_PIXEL_BORDER (byte) 3
#define DOWN_PIXEL_BORDER (byte) PIXEL_DISPLAY_LEN - 2
#define LEFT_PIXEL_BORDER (byte) 0
#define RIGHT_PIXEL_BORDER (byte) PIXEL_DISPLAY_LEN

#define OBSTACL_H (byte) 16
#define OBSTACL_W (byte) 16

#define LEFT (byte) 1
#define RIGHT (byte) 2
#define UP (byte) 1
#define DOWN (byte) 2 
