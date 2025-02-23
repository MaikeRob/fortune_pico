#include "../headers/display.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../lib/pico-ssd1306/ssd1306.h"


#define I2C_PORT i2c1
#define SDA_PIN 14
#define SCL_PIN 15
#define DISPLAY_ADDR 0x3C

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

static ssd1306_t disp;


void setup_display() {

    // Inicializa comunicação i2c com o display com velocidade configurada em 400kHz
    i2c_init(I2C_PORT, 400000);

    // Configura os pinos SDA e SCL para funcionarem como I2C
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // Configura os pinos SDA e SCL para pull-up
    // Evita que o barramento fique flutuando
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    disp.external_vcc=false;
    ssd1306_init(&disp, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_ADDR, I2C_PORT);
    ssd1306_clear(&disp);
    ssd1306_show(&disp);

}

void deinitialize_display() {
    ssd1306_deinit(&disp);
}

void clear_display() {
    ssd1306_clear(&disp);
}

void draw_point(int x, int y) {
    ssd1306_draw_pixel(&disp, (uint32_t)x, (uint32_t)y);
    ssd1306_show(&disp);
}

void clear_point(int x, int y) {
    ssd1306_clear_pixel(&disp, (uint32_t)x, (uint32_t)y);
}