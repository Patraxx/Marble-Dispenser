#include "servo.h"


void initialize_servo()
{
    // Configure the LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_16_BIT,
        .freq_hz = 50, // Frequency in Hertz
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Configure the LEDC channel
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = SERVO_PIN,
        .duty = 0, // Initial duty cycle
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}



void set_servo_speed(int speed)    // ellan 1 till 100 och -1 och -100
{    
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;
    // Calculate the duty cycle

    uint32_t pulsewidth = SERVO_NEUTRAL_PULSEWIDTH + (speed * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) / 200);

    // Scale the pulse width to the timer resolution
    uint32_t duty = (pulsewidth * SERVO_MAX_DUTY) / 20000; // 20000 microseconds for 50Hz

    printf("Speed: %d, Pulsewidth: %lu, Duty: %lu\n", speed, pulsewidth, duty);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    /*
    
    uint32_t pulse_width = SERVO_NEUTRAL_PULSEWIDTH + (speed * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) / 200);

    // Convert pulse width (in microseconds) to duty cycle
    uint32_t duty = pulse_width * (1 << LEDC_TIMER_16_BIT) / SERVO_MAX_PULSEWIDTH;

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    
    */
}