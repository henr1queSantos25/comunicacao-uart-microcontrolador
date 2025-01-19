#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "pico/bootrom.h"

#define BUZZER 21

void initBuzzer(){
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

void buzzer_on(uint buzzer_pin, float frequency, uint duration_ms){
    float period = 1.0f / frequency;                        // Período da onda quadrada
    float half_period = period / 2;                         // Meio período em segundos
    uint cycles = (uint)((duration_ms / 1000.0f) / period); // Número de ciclos

    for (uint i = 0; i < cycles; i++)
    {
        gpio_put(buzzer_pin, 1);            // Seta o pino como HIGH
        sleep_us((int)(half_period * 1e6)); // Espera pelo meio período
        gpio_put(buzzer_pin, 0);            // Seta o pino como LOW
        sleep_us((int)(half_period * 1e6)); // Espera pelo meio período
    }
}



int main(){
    char comando[32];
    stdio_init_all();
    initBuzzer();
   

    while (true) {
        scanf("%s", comando);
        
        // ACIONA O BUZZER POR 2 SEGUNDOS
        if(strcmp(comando, "BUZZER") == 0 || strcmp(comando, "buzzer") == 0){
            buzzer_on(21, 440, 2000);
            printf("BUZZER ACIONADO!\n");
        }
        else if(strcmp(comando, "REBOOT") == 0 || strcmp(comando, "reboot") == 0) { 
            printf("INICIALIZANDO O MODO DE GRAVAÇÃO...\n");
            reset_usb_boot(0, 0);
        }
        else{
            printf("COMANDO INVALIDO!!!\n");
        }
    }
}
