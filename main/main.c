#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//23 = 2nd column, 21 == 1st column, 19 == 3rd column
// 22 == 1st row, 20 == 2nd row, 18 == 3rd row, 15 == 4th row

int row_pins[] = {22, 20, 18, 15}; // Based on keypad's documentation for row mapping
int col_pins[] = {21, 23, 19};

void app_main(void)
{


    

}