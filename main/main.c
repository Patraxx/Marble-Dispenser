#include "driver/gpio.h"
#include "extra.h"
#include "servo.h"

//23 = 2nd column, 21 == 1st column, 19 == 3rd column
// 22 == 1st row, 20 == 2nd row, 18 == 3rd row, 15 == 4th row



void app_main(void)
{
    initialize_gpio();
    initialize_servo();

    while(1){

        scan_keypad();
        
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}