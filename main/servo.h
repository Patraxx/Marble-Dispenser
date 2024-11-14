#ifndef SERVO_H
#define SERVO_H

#include "extra.h"
#include "driver/ledc.h"

#define SERVO_PIN 14 // GPIO pin connected to the servo
#define SERVO_NEUTRAL_PULSEWIDTH 1500 // Neutral pulse width in microseconds
#define SERVO_MIN_PULSEWIDTH 1000 // Minimum pulse width in microseconds
#define SERVO_MAX_PULSEWIDTH 2000 

void initialize_servo();

void set_servo_speed(int speed);









#endif // EXTRA_H