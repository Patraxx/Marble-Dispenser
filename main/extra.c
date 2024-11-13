#include "extra.h"

int row_pins[] = {22, 20, 18, 15}; // Based on keypad's documentation for row mapping
int col_pins[] = {21, 23, 19};

char input_code[CODE_LENGTH+1]; // +1 for null terminator

void add_to_code(char key)
{
    static int index = 0;
    if (index < CODE_LENGTH)
    {
        input_code[index] = key;
        index++;
    }
    else
    {
        printf("Code is full\n");
    }
}

char keymap[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
    

void initialize_gpio()
{
    for (int i = 0; i < 4; i++)
    {
        esp_rom_gpio_pad_select_gpio(row_pins[i]);
        gpio_set_direction(row_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(row_pins[i], 0);
    }

    for (int i = 0; i < 3; i++)
    {
        esp_rom_gpio_pad_select_gpio(col_pins[i]);
        gpio_set_direction(col_pins[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(col_pins[i], GPIO_PULLUP_ONLY);
    }
    esp_rom_gpio_pad_select_gpio(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(led_pin, 0);
}

void scan_keypad()
{   
    for (int i = 0; i < 4; i++)
        {
            gpio_set_level(row_pins[i], 0);
            for (int j = 0; j < 3; j++)
            {
                if (gpio_get_level(col_pins[j]) == 0)
                {                
                    printf("Key pressed: %c\n", keymap[i][j]);
                   // add_to_code(keymap[i][j]);   
                    set_servo_speed(10);                           
                    gpio_set_level(led_pin, 1);
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(led_pin, 0);
                    set_servo_speed(0);
                }
            }
            gpio_set_level(row_pins[i], 1);
        
        }
}