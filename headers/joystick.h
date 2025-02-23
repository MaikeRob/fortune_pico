#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"

void setup_joystick();

uint16_t get_joystick_x_position();

uint16_t get_joystick_y_position();

#endif