#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "servo.h"
#include <string.h>


void initialize_gpio();

void scan_keypad();




#endif // EXTRA_H