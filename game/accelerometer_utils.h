#define HEADERFILE_ACCELEROMETER_UTILS

#define LEFT_MOVE 335
#define RIGHT_MOVE 345

const int xpin = A0;
const int ypin = A1;
const int zpin = A2;

static int z_last;

uint8_t get_direction(uint8_t last_direction) {
    int current = analogRead(zpin);

    if(current < LEFT_MOVE)
        return LEFT;
    if(current > RIGHT_MOVE)
        return RIGHT;
}
