#define HEADERFILE_ACCELEROMETER_UTILS

#define LEFT_MOVE 342
#define RIGHT_MOVE 353

#define ZPIN A2

uint8_t get_direction(uint8_t last_direction) {
    int current = analogRead(ZPIN);

    if (current < LEFT_MOVE)
        return LEFT;
    if (current > RIGHT_MOVE)
        return RIGHT;
}
