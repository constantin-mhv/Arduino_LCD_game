#define LEFT_BUTTON (byte) 2
#define MIDDLE_BUTTON (byte) 3
#define RIGHT_BUTTON (byte) 4

#ifndef HEADERFILE_CONSTANTS
#include "constants.h"
#endif

byte first_platform = 15;
byte last_platform = 17;

void move_platform(byte direction);
void activate_buttons();

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
