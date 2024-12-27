#include "driver/gpio.h"
#include "driver/adc.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
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


void raw_adc_task(void *arg)
{
        int adc_value = 0;

    while (1)
    {     
        adc_value = adc1_get_raw(ADC1_CHANNEL_5);
       // printf("adc value: %d\n", adc_value);
        if (adc_value > 120)
        {
            printf(" Marble detected, stopping servo-sequence  ");
            servo_duty = DUTY;
            piezo_triggered = true;
            correct_code = false;
            xTaskNotify(green_LED_handle, 0, eNoAction);
            printf("adc value: %d\n", adc_value);
            vTaskDelay(400 / portTICK_PERIOD_MS);           
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void green_LED_task(void *arg)
{
    while (1)
    {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) == pdTRUE)
        {
            printf("Green LED on\n");
            gpio_set_level(LED_PIN_GREEN, 1);
            vTaskDelay(200 / portTICK_PERIOD_MS);
            gpio_set_level(LED_PIN_GREEN, 0);
        } 
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void red_LED_task(void *arg)
{
    while (1)
    {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) == pdTRUE)
        {
            for(int i = 0; i < 5; i++)
            {
                gpio_set_level(LED_PIN_RED, 1);
                vTaskDelay(100 / portTICK_PERIOD_MS);
                gpio_set_level(LED_PIN_RED, 0);
                vTaskDelay(100 / portTICK_PERIOD_MS);
            }
            printf("FALSE code \n");
            vTaskDelay(50 / portTICK_PERIOD_MS);
         
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

TaskHandle_t green_LED_handle;
TaskHandle_t red_LED_handle;



void app_main(void)
{  
    initalize_input_piezo();
    initialize_gpio();
    initialize_LED();
    initialize_servo();
   // initialize_buttons();

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);

  
  //  xTaskCreate(button_reading_task_servo_session, "button_reading_task", 2048, NULL, 10, NULL);
    xTaskCreate(green_LED_task, "green_LED_task", 2048, NULL, 10, &green_LED_handle);
    xTaskCreate(raw_adc_task, "piezo_task", 2048, NULL, 10, NULL);
    xTaskCreate(red_LED_task, "red_LED_task", 2048, NULL, 10, &red_LED_handle);

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

   
}

