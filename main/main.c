#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"


void app_main(void)
{
    initialize_gpio();
    initialize_servo();

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}