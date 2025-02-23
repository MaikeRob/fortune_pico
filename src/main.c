#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../headers/display.h"
#include "../headers/joystick.h"


int main() {

    stdio_init_all();

    setup_display();
    setup_joystick();

    for(int i = 0; i < 128; i++) {
        for(int j = 0; j < 64; j++) {
            draw_point(i, j);
            printf("x: %d, y: %d\n", get_joystick_x_position(), get_joystick_y_position());
        }
    }

    deinitialize_display();

    return 0;
}
