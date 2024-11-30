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


void app_main(void)
{  
    initalize_input_piezo();
    initialize_gpio();
    initialize_buttons();
  
    initialize_servo();
    int piezo = 0;

    while (1)
    {
        piezo = gpio_get_level(PIEZO_PIN);
        /* code */
        printf("Piezo: %d\n", piezo);
        if (piezo == 1)
        {
            move_servo();
            vTaskDelay(300 / portTICK_PERIOD_MS); // Debounce delay
            stop_servo();
        }
        

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);
   
  
    xTaskCreate(button_reading_task_for_servo, "button_reading_task", 2048, NULL, 10, NULL);

   
}

