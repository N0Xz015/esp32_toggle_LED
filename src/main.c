#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_task_wdt.h"

const gpio_num_t LED_PIN_1 = GPIO_NUM_13;
const gpio_num_t LED_PIN_2 = GPIO_NUM_12;
const gpio_num_t LED_PIN_3 = GPIO_NUM_11;

#define BLINK_AMOUNT 10 
#define BLINK_PERIOD_MS 2000

void app_main() {

    size_t BLINK_COUNT = 0;
    uint64_t CURRENT_TIME = 0;
    uint64_t LAST_TOGGLE  = 0;
    
    gpio_set_level(LED_PIN_1, 0);
    gpio_set_level(LED_PIN_2, 0);
    gpio_set_level(LED_PIN_3, 0);
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_3, GPIO_MODE_OUTPUT);
    

    while (1) {  
        CURRENT_TIME = (uint64_t) (esp_timer_get_time() / 1000);
        
        if (CURRENT_TIME - LAST_TOGGLE >= BLINK_PERIOD_MS) { 
            gpio_set_level(LED_PIN_2, 0);
            LAST_TOGGLE = CURRENT_TIME;
            
            if (LED_PIN_1 == 0) { // when time has come if LED off set to on
                gpio_set_level(LED_PIN_1, 1);   
            }
            else { // when time has come if LED on turn it off
                gpio_set_level(LED_PIN_1, 0);
                gpio_set_level(LED_PIN_2, 1);// turn LED on every time that BLINK_COUNT increase
                BLINK_COUNT++;
            }
        }
        if(BLINK_COUNT >= BLINK_AMOUNT) {
            gpio_set_level(LED_PIN_3, 1);// this LED related to is progress done // this work well
            gpio_set_level(LED_PIN_2, 1);// should toggle but it's always on
            gpio_set_level(LED_PIN_1, 1);// it not blink or blink too fast?
            break;
        }
    }
}