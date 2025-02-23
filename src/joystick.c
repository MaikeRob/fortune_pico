#include "../headers/joystick.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"


#define JOYSTICK_X_PIN 26
#define JOYSTICK_Y_PIN 27
#define TRANSFER_COUNT 1000000

static volatile uint16_t buffer[2];


static int dma_chan;

void dma_handler() {
    // Limpa a flag de interrupção do canal
    dma_hw->ints0 = 1u << dma_chan;

    // Reinicia o DMA para continuar capturando dados
    dma_channel_start(dma_chan);
}

void setup_adc() {
    adc_init();

    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);


    //adc_select_input(0);
    adc_set_round_robin(0x03);

    adc_fifo_setup(
      true,
      true,
      2,
      false,
      false
    );
}

void setup_dma() {
    dma_chan = dma_claim_unused_channel(true);
    dma_channel_config cfg = dma_channel_get_default_config(dma_chan);

    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    channel_config_set_dreq(&cfg, DREQ_ADC);
    channel_config_set_ring(&cfg, true, 2);

    dma_channel_configure(
      dma_chan,
      &cfg,
      buffer,
      &adc_hw->fifo,
      TRANSFER_COUNT,
      false
    );

    dma_channel_set_irq0_enabled(dma_chan, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

void setup_joystick() {
    setup_adc();
    setup_dma();

    adc_fifo_drain();
    dma_channel_start(dma_chan);
    adc_run(true);
}

uint16_t get_joystick_x_position() {
    return buffer[0];
}

uint16_t get_joystick_y_position() {
    return buffer[1];
}