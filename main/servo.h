#ifndef SERVO_H
#define SERVO_H

#include "keypad.h"
#include "driver/ledc.h"

#define SERVO_PIN 13 // GPIO pin connected to the servo

#define SERVO_NEUTRAL_PULSEWIDTH 1500 // Neutral pulse width in microseconds
#define SERVO_MIN_PULSEWIDTH 1000 // Minimum pulse width in microseconds
#define SERVO_MAX_PULSEWIDTH 2000 

void initialize_servo();

void set_servo_speed();
void stop_servo();
void move_servo_after_correct_code();




#endif // EXTRA_H