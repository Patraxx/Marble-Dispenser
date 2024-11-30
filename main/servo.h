#ifndef SERVO_H
#define SERVO_H

#include "keypad.h"
#include "driver/ledc.h"
#define MAX_DUTY 1023  // Max duty cycle (adjust to your resolution, e.g., 13-bit)
#define MIN_DUTY 0 
#define SERVO_PIN 7// GPIO pin connected to the servo
#define DUTY 630

#define SERVO_NEUTRAL_PULSEWIDTH 1500 // Neutral pulse width in microseconds
#define SERVO_MIN_PULSEWIDTH 1000 // Minimum pulse width in microseconds
#define SERVO_MAX_PULSEWIDTH 2000 

void initialize_servo();

void stop_servo();
void move_servo();
void increase_servo_duty();
void decrease_servo_duty();
int is_servo_running();




#endif // EXTRA_H