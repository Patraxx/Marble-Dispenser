#include "keypad.h"
#include "code_code.h"
#include "servo.h"

int row_pins[] = {22, 15, 18, 23}; // Based on keypad's documentation for row mapping
int col_pins[] = {21, 20, 19};
int code_index = 0;
extern char input_code[CODE_LENGTH + 1];
volatile bool correct_code = false;

char keymap[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

void reset_input_code()
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        input_code[i] = '\0';
    }
    code_index = 0;
    
}
    

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

}

void code_correct_loop(){
    int counter = 0;

    while(correct_code)
    {  
        move_servo();
        counter++;
        vTaskDelay(SERVO_DURATION/ portTICK_PERIOD_MS);
        stop_servo();   
        vTaskDelay(500/ portTICK_PERIOD_MS); 
        if(counter > 5){
            correct_code = false;
        }        
        //start a servo counter. if the servo has gone through more than 10 loops, stop it.                                                      
    }

}

void scan_keypad(void *pvParameters)
{   
    //correct_code = false;
    while(1)
    {

        for (int i = 0; i < 4; i++)
            {
                gpio_set_level(row_pins[i], 0);
                for (int j = 0; j < 3; j++)
                {
                    if (gpio_get_level(col_pins[j]) == 0)
                    {   
                        // lägg till ett sätt att avbryta kodinmatning och börja om
                        printf("Key pressed: %c\n", keymap[i][j]);
                        add_to_code(keymap[i][j], &code_index);                                         
                        vTaskDelay(200 / portTICK_PERIOD_MS);
                                              
                    if(code_index == CODE_LENGTH){ 

                        correct_code = use_code(input_code);
                                
                        if(correct_code){
                            printf("Correct code entered\n");
                            code_correct_loop();
                        }
                        else{
                            printf("Incorrect code entered\n");
                        }                                
                        reset_input_code(); 
                        code_index = 0;  
                    }                                
                    vTaskDelay(20 / portTICK_PERIOD_MS);
                }
                  
            }
            gpio_set_level(row_pins[i], 1);      
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}