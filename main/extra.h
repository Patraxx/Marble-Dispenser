#ifndef EXTRA_H
#define EXTRA_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "servo.h"


#define led_pin GPIO_NUM_12
#define CODE_LENGTH 4

void initialize_gpio();

void scan_keypad();






#endif // EXTRA_H