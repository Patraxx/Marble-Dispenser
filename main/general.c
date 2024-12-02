#include "general.h"


void initialize_buttons(void)
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << BUTTON_PIN1) | (1 << BUTTON_PIN2) | (1 << BUTTON_PIN3);
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_ENABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}
void initialize_LED(void)
{
    gpio_config_t config;
    config.pin_bit_mask = (1 << LED_PIN_GREEN, 1 << LED_PIN_RED);
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_ENABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
}

void button_reading_task_for_servo(void *arg)  //button reading, but reserved for servo
{
    while (1)
    {
        // Button 1: Start/stop servo
        if (gpio_get_level(BUTTON_PIN1) == 0) // Button 1 is pressed
        {
            move_servo();
            vTaskDelay(300/ portTICK_PERIOD_MS); // Debounce delay
            stop_servo();
        }
        // Button 2: Increase duty
        if (gpio_get_level(BUTTON_PIN2) == 0) // Button 2 is pressed
        {
            //increase duty
            increase_servo_duty();
            vTaskDelay(300 / portTICK_PERIOD_MS); // Debounce delay
        }
        // Button 3: Decrease duty
        if (gpio_get_level(BUTTON_PIN3) == 0) // Button 3 is pressed
        {
            decrease_servo_duty();
            vTaskDelay(300 / portTICK_PERIOD_MS); // Debounce delay
        }

        vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to reduce CPU usage
    }

    vTaskDelete(NULL); // Delete the task if it ever exits the loop
}

/*

typedef struct {
    gpio_num_t button_pin;          // GPIO pin for the button
    void (*button_action)(void);    
    


void button_reading_task(void *arg)
{
    button_config_t *buttons = (button_config_t *)arg; // Array of button configurations
    size_t button_count = 3;                           // Number of buttons

    while (1)
    {
        for (size_t i = 0; i < button_count; i++)
        {
            if (gpio_get_level(buttons[i].button_pin) == 0) // Button is pressed
            {
                buttons[i].button_action();                 // Execute the button's action
                vTaskDelay(buttons[i].debounce_delay);      // Debounce delay
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to reduce CPU usage
    }

    vTaskDelete(NULL); // Delete the task if it ever exits the loop
}



 gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN1) | (1ULL << BUTTON_PIN2) | (1ULL << BUTTON_PIN3),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    // Define button configurations
    static button_config_t button_configs[] = {
        {BUTTON_PIN1, toggle_servo, 300 / portTICK_PERIOD_MS},
        {BUTTON_PIN2, increase_duty, 300 / portTICK_PERIOD_MS},
        {BUTTON_PIN3, decrease_duty, 300 / portTICK_PERIOD_MS},
    };

    // Create a single task for handling all buttons
    xTaskCreate(button_reading_task, "button_task", 2048, button_configs, 5, NULL);


*/
