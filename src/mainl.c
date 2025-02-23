#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../headers/display.h"


int main() {

    stdio_init_all();

    setup_display();

    for(int i = 0; i < 128; i++) {
        for(int j = 0; j < 64; j++) {
            draw_point(i, j);
        }
    }

    draw_point(50, 50);

    deinitialize_display();

    return 0;
}
