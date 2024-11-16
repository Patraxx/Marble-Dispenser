#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"


void initialize_buttons(void)
{
   
    gpio_config_t config;
    config.pin_bit_mask = (1 << 10) | (1 << 11);
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_ENABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}

void servo_chatgpt(){


    // Set neutral position (about 1500 µs pulse)
    int neutral_duty = 1500 / 9.77; // Calculate duty for neutral position
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, neutral_duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(pdMS_TO_TICKS(1000)); // Wait a moment in neutral

    // Small movement - adjust duty slightly above neutral
    int small_move_duty = neutral_duty + 10; // Fine-tune this step value for minimal movement
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, small_move_duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(pdMS_TO_TICKS(500)); // Move for half a second

    // Return to neutral to stop the servo
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, neutral_duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(pdMS_TO_TICKS(1000)); // Wait a moment in neutral

}
void move_servo(int speed)    // ellan 1 till 100 och -1 och -100
{    
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;
    // Calculate the duty cycle

    uint32_t pulsewidth = SERVO_NEUTRAL_PULSEWIDTH + (speed * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) / 200);

    // Scale the pulse width to the timer resolution
    uint32_t duty = (pulsewidth * 2047) / 20000; 

    printf("Speed: %d, Pulsewidth: %lu, Duty: %lu\n", speed, pulsewidth, duty);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    // Move the servo for about half a second
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // Stop the servo by setting it to the neutral position
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (SERVO_NEUTRAL_PULSEWIDTH * 2047) / 20000);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    
}


void read_servo_buttons(void *pvParameters){

    while(1){
        if(gpio_get_level(10) == 0){
            set_servo_speed(10);
        }
        else if(gpio_get_level(11) == 0){
            servo_chatgpt();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    initialize_gpio();
    initialize_buttons();
    initialize_servo();
<<<<<<< HEAD

    while(1)
    {
        
        set_servo_speed();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        stop_servo();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
=======
>>>>>>> 8732fda12905974d10b00a689c60aea79d79f55e

    xTaskCreate(read_servo_buttons, "read_servo_buttons", 2048, NULL, 10, NULL);
    
  //  xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}

