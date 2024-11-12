#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//23 = 2nd column, 21 == 1st column, 19 == 3rd column
// 22 == 1st row, 20 == 2nd row, 18 == 3rd row, 15 == 4th row

int row_pins[] = {22, 20, 18, 15}; // Based on keypad's documentation for row mapping
int col_pins[] = {21, 23, 19};
#define led_pin GPIO_NUM_12

void initialize_gpio()
{
    for (int i = 0; i < 4; i++)
    {
        esp_rom_gpio_pad_select_gpio(row_pins[i]);
        gpio_set_direction(row_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(row_pins[i], 0);
    }

    for (int i = 0; i < 3; i++)
    {
        esp_rom_gpio_pad_select_gpio(col_pins[i]);
        gpio_set_direction(col_pins[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(col_pins[i], GPIO_PULLUP_ONLY);
    }
    esp_rom_gpio_pad_select_gpio(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(led_pin, 0);
}

void app_main(void)
{
    initialize_gpio();

    while(1){
        for (int i = 0; i < 4; i++)
        {
            gpio_set_level(row_pins[i], 0);
            for (int j = 0; j < 3; j++)
            {
                if (gpio_get_level(col_pins[j]) == 0)
                {
                    printf("Button pressed at row %d and column %d\n", i, j);
                     
                    
                    gpio_set_level(led_pin, 1);
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(led_pin, 0);
                }
            }
            gpio_set_level(row_pins[i], 1);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}