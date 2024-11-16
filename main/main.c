#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"


void app_main(void)
{
    initialize_gpio();
    initialize_servo();

    while(1)
    {
        
        set_servo_speed();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        stop_servo();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

    

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}

