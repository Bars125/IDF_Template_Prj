#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/freeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_26,GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_26, 0);
    while(true){
        gpio_set_level(GPIO_NUM_26, 1);
        vTaskDelay(1000);
        gpio_set_level(GPIO_NUM_26, 0);
        vTaskDelay(1000);
    }
}
