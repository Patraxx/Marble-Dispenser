#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"

int servo_speed = 100;

void initialize_buttons(void)
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << 5) | (1 << 6) | (1 << 7);
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_ENABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}

void set_servo_speed()    // ellan 1 till 100 och -1 och -100
{    
    printf("Setting servo speed\n");
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, servo_speed);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

}

void stop_servo()
{
 printf("Stopping servo\n");
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}



void read_servo_buttons(void *pvParameters){

    while(1){

        if(gpio_get_level(5) == 0){
            set_servo_speed();
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else if(gpio_get_level(6) == 0){
            stop_servo();
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else if(gpio_get_level(7) == 0){
            servo_speed += 10;
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }   
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    initialize_gpio();
    initialize_buttons();
    initialize_servo();

    

    xTaskCreate(read_servo_buttons, "read_servo_buttons", 2048, NULL, 10, NULL);
    
  //  xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}

