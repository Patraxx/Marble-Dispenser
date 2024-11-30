#include "driver/gpio.h"
#include "keypad.h"
#include "servo.h"
#include "code_code.h"
#include "general.h"




void app_main(void)
{  

    initialize_gpio();
    initialize_buttons();
  
    initialize_servo();

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);
   
  
    xTaskCreate(button_reading_task_for_servo, "button_reading_task", 2048, NULL, 10, NULL);

   
}

