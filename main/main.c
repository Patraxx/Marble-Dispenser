#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"
#include "general.h"

#define PIEZO_PIN 5


void initalize_input_piezo()
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << PIEZO_PIN);
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}

void piezo_task(void *arg)
{
    while (1)
    {
        if (gpio_get_level(PIEZO_PIN) == 1)
        {
            printf("Piezo is pressed\n");
            vTaskDelay(100 / portTICK_PERIOD_MS);
            correct_code = true;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{  
    initalize_input_piezo();
    initialize_gpio();
    initialize_buttons();
    initialize_servo();
  

   
    xTaskCreate(piezo_task, "piezo_task", 2048, NULL, 10, NULL);

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);
   
  
    xTaskCreate(button_reading_task_for_servo, "button_reading_task", 2048, NULL, 10, NULL);

   
}

