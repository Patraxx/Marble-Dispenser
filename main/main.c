#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"

int servo_speed = 500;

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

void app_main(void)
{
    initialize_gpio();
  
    initialize_servo();

    

    
    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}

