#ifndef GENERAL_H
#define GENERAL_H
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "code_code.h"
#include "servo.h"

#define BUTTON_PIN1 2
#define BUTTON_PIN2 3
#define BUTTON_PIN3 4
#define LED_PIN_GREEN 6
#define LED_PIN_RED 8

void initialize_buttons(void);
void initialize_LED(void);
void button_reading_task_for_servo(void *arg);


#endif // GENERAL_H