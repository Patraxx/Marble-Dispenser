#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"


void initialize_buttons(void)
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << 2) | (1 << 3) | (1 << 4);
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_ENABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}

void initialize_LED(void)
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << LED_PIN_RED);
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_ENABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}


void app_main(void)
{
   // initialize_gpio();
  
    initialize_servo();

    while(1)
    {   
        move_servo_after_correct_code();
        vTaskDelay(500 / portTICK_PERIOD_MS);
        stop_servo();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    
  //  xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}

