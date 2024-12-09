#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "servo.h"
#include <string.h>

volatile extern bool correct_code;
void initialize_gpio();

void scan_keypad();

void code_correct_loop();

void reset_input_code();




#endif // EXTRA_H