#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "pico/bootrom.h"

#define BUZZER 21
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13

void setLeds(bool r, bool g, bool b)
{
    gpio_put(LED_PIN_RED, r);
    gpio_put(LED_PIN_GREEN, g);
    gpio_put(LED_PIN_BLUE, b);
}

void initLeds()
{
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    
}

void initBuzzer()
{
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

void buzzer_on(uint buzzer_pin, float frequency, uint duration_ms)
{
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

int main()
{
    char comando[32];
    initLeds();
    initBuzzer();
    stdio_init_all();
    initBuzzer();

    while (true)
    {
        scanf("%s", comando);

        if (strcmp(comando, "GREEN") == 0 || strcmp(comando, "green") == 0)
        {
            setLeds(0, 1, 0);
            printf("LED VERDE LIGADO!\n");
        }
        else if (strcmp(comando, "RED") == 0 || strcmp(comando, "red") == 0)
        {
            setLeds(1, 0, 0);
            printf("LED VERMELHO LIGADO!\n");
        }
        else if(strcmp(comando, "BLUE") == 0 || strcmp(comando, "blue") == 0)
        {
            setLeds(0,0,1);
            printf("LED AZUL LIGADO!\n");
        }
        else if (strcmp(comando, "OFF") == 0 || strcmp(comando, "off") == 0)
        {
            setLeds(0, 0, 0);
            printf("LEDS DESLIGADOS!\n");
        }
        else if(strcmp(comando, "WHITE") == 0 || strcmp(comando, "white") == 0)
	    {
            setLeds(1, 1, 1);
            printf("LED BRANCO LIGADO!\n");
        }
        // ACIONA O BUZZER POR 2 SEGUNDOS
        else if (strcmp(comando, "BUZZER") == 0 || strcmp(comando, "buzzer") == 0)
        {
            buzzer_on(21, 440, 2000);
            printf("BUZZER ACIONADO!\n");
        }
        else if (strcmp(comando, "REBOOT") == 0 || strcmp(comando, "reboot") == 0)
        {
            printf("INICIALIZANDO O MODO DE GRAVAÇÃO...\n");
            reset_usb_boot(0, 0);
        }
        else
        {
            printf("COMANDO INVALIDO!!!\n");
        }
    }
}
