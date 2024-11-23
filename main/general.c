#include "general.h"


void initialize_buttons(void)
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << BUTTON_PIN1) | (1 << 3) | (1 << 4);
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

void button_reading_task(void *arg)  //button reading, but reserved for servo
{
    while (1)
    {
        // Button 1: Start/stop servo
        if (gpio_get_level(BUTTON_PIN1) == 0) // Button 1 is pressed
        {
            if (is_servo_running())
            {
               stop_servo();
            }
            else
            {                        
               move_servo();             
            }
            vTaskDelay(300/ portTICK_PERIOD_MS); // Debounce delay
        }
        // Button 2: Increase duty
        if (gpio_get_level(BUTTON_PIN1) == 0) // Button 2 is pressed
        {
            //increase duty
            increase_servo_duty();
            vTaskDelay(300 / portTICK_PERIOD_MS); // Debounce delay
        }
        // Button 3: Decrease duty
        if (gpio_get_level(BUTTON_PIN3) == 0) // Button 3 is pressed
        {
            //decrease duty
            vTaskDelay(300 / portTICK_PERIOD_MS); // Debounce delay
        }

        vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to reduce CPU usage
    }

    vTaskDelete(NULL); // Delete the task if it ever exits the loop
}
