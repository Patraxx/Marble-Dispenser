#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "servo.h"
#include <string.h>


#define LED_PIN_RED GPIO_NUM_9

#define LED_PIN_GREEN GPIO_NUM_12


void initialize_gpio();

void scan_keypad();




#endif // EXTRA_H