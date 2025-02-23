#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#define JOYSTICK_X_PIN 26
#define JOYSTICK_Y_PIN 27

volatile uint16_t buffer[2];

int main() {

  stdio_init_all();

  adc_init();

  adc_gpio_init(JOYSTICK_X_PIN);
  adc_gpio_init(JOYSTICK_Y_PIN);


  adc_select_input(0);
  adc_set_round_robin(0x03);

  adc_fifo_setup(
    true,
    true,
    1,
    false,
    false
  );

  int dma_chan;
  dma_channel_config cfg;

  dma_chan = dma_claim_unused_channel(true);
  cfg = dma_channel_get_default_config(dma_chan);

  channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);

  channel_config_set_read_increment(&cfg, false);

  channel_config_set_write_increment(&cfg, true);

  channel_config_set_dreq(&cfg, DREQ_ADC);

  channel_config_set_chain_to(&cfg, dma_chan);

  dma_channel_configure(
    dma_chan,
    &cfg,
    buffer,
    &adc_hw->fifo,
    2,
    true
  );

  adc_run(true);

  while (true) {

    uint16_t x = buffer[0];
    uint16_t y = buffer[1];
    printf("X: %u, Y: %u\n", x, y);
    printf("kjk\n");
  }

}