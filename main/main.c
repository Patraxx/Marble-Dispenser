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
   // printf("Rotating servo one way...\n");
    set_servo_speed(-10);  // Rotate the servo to 40% speed
 
    vTaskDelay(2000 / portTICK_PERIOD_MS);  // Run for 2 seconds

  //  printf("Stopping servo...\n");
    set_servo_speed(-30);  // Stop the servo
 
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    }

    

    xTaskCreate(scan_keypad, "scan_keypad", 2048, NULL, 10, NULL);

}

