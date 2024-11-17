#include "servo.h"


void initialize_servo()
{
    // Configure the LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_13_BIT, // 0-2047
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

void move_servo_after_correct_code()
{
    printf("Moving servo\n");
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 650);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}
void stop_servo()
{
 printf("Stopping servo\n");
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}


