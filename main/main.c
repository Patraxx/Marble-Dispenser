#include "driver/gpio.h"
#include "driver/adc.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"
#include "general.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

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
        esp_adc_cal_raw_to_voltage(ADC1_CHANNEL_2,);
        printf("ADC value: %d\n", adc_value);
        if (adc_value < 2500)
        {
          //  printf("Piezo is pressed\n");
           // move_servo();
           // vTaskDelay(300 / portTICK_PERIOD_MS);
           // stop_servo();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

    }
}


void app_main(void)
{  
   // initalize_input_piezo();
    initialize_gpio();
    initialize_buttons();
    initialize_servo();

    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);

   
    xTaskCreate(raw_adc_task, "piezo_task", 2048, NULL, 10, NULL);

    //xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);
   
  
    //xTaskCreate(button_reading_task_for_servo, "button_reading_task", 2048, NULL, 10, NULL);

   
}

