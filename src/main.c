#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main() {
    // Inicializa a saída serial (USB CDC) para imprimir no terminal
    stdio_init_all();
    sleep_ms(2000); // Aguarda 2 segundos para a conexão serial ser estabelecida

    // Inicializa o ADC
    adc_init();

    // Configura os pinos para os canais ADC:
    // GPIO26 -> ADC0 (eixo X) e GPIO27 -> ADC1 (eixo Y)
    adc_gpio_init(26);  // Canal 0
    adc_gpio_init(27);  // Canal 1

    // Configura o ADC para modo round robin lendo canais 0 e 1
    adc_set_round_robin((1 << 0) | (1 << 1));

    adc_select_input(0);

    // Configura o FIFO do ADC:
    // - Habilita o FIFO
    // - Habilita o DREQ (útil para DMA, mesmo que não usemos DMA aqui)
    // - Define o nível de disparo como 1 (quando há pelo menos 1 amostra, pode ser lido)
    // - Não gera erro no caso de overflow e não empacota as amostras
    adc_fifo_setup(true, true, 1, false, false);

    // Limpa o FIFO (se necessário)
    while (adc_fifo_get_level() > 0) {
        adc_fifo_get();
    }

    // Inicia as conversões do ADC
    adc_run(true);

    // Loop principal
    while (true) {
        // Verifica se há pelo menos 2 amostras disponíveis no FIFO
        if (adc_fifo_get_level() >= 2) {
            // Como usamos round robin para canais 0 e 1,
            // a primeira amostra corresponde ao canal 0 (eixo X)
            // e a segunda ao canal 1 (eixo Y)
            uint16_t sample_x = adc_fifo_get();
            uint16_t sample_y = adc_fifo_get();

            // Imprime os valores lidos no terminal
            printf("Eixo X: %d  |  Eixo Y: %d\n", sample_x, sample_y);
        }
        sleep_ms(500); // Pequena pausa para evitar saturar o terminal
    }

    return 0;
}
