#ifndef DISPLAY_H
#define DISPLAY_H

// Função para configurar comunicação I2C com o display na BitDogLab
void setup_display();

void deinitialize_display();

void clear_display();

void draw_point(int x, int y);

#endif