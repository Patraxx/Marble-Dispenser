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

#define BUTTON1_PIN 2// GPIO pin for Button 1
#define BUTTON2_PIN 3 // GPIO pin for Button 2
#define BUTTON3_PIN 4 // GPIO pin for Button 3
#define MAX_DUTY 1023  // Max duty cycle (adjust to your resolution, e.g., 13-bit)
#define MIN_DUTY 0     // Min duty cycle

volatile int servo_duty = 0; // Global variable for duty cycle

void button_reading_task(void *arg)
{
    // Configure the button GPIOs as inputs with pull-ups
    gpio_config_t btn_config = {
        .pin_bit_mask = (1ULL << BUTTON1_PIN) | (1ULL << BUTTON2_PIN) | (1ULL << BUTTON3_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&btn_config);

    while (1)
    {
        // Button 1: Start/stop servo
        if (gpio_get_level(BUTTON1_PIN) == 0) // Button 1 is pressed
        {
            if (servo_duty != 0)
            {
                printf("Button 1 pressed: Starting servo with duty %d\n", servo_duty);
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, servo_duty);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            }
            else
            {
                printf("Button 1 pressed: Stopping servo\n");
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            }
            vTaskDelay(100 / portTICK_PERIOD_MS); // Debounce delay
        }

        // Button 2: Increase duty
        if (gpio_get_level(BUTTON2_PIN) == 0) // Button 2 is pressed
        {
            if (servo_duty + 10 <= MAX_DUTY)
            {
                servo_duty += 10;
                printf("Button 2 pressed: Increasing duty to %d\n", servo_duty);
            }
            else
            {
                printf("Button 2 pressed: Duty at maximum (%d)\n", MAX_DUTY);
            }
            vTaskDelay(100 / portTICK_PERIOD_MS); // Debounce delay
        }

        // Button 3: Decrease duty
        if (gpio_get_level(BUTTON3_PIN) == 0) // Button 3 is pressed
        {
            if (servo_duty - 10 >= MIN_DUTY)
            {
                servo_duty -= 10;
                printf("Button 3 pressed: Decreasing duty to %d\n", servo_duty);
            }
            else
            {
                printf("Button 3 pressed: Duty at minimum (%d)\n", MIN_DUTY);
            }
            vTaskDelay(100 / portTICK_PERIOD_MS); // Debounce delay
        }

        vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to reduce CPU usage
    }

    vTaskDelete(NULL); // Delete the task if it ever exits the loop
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

