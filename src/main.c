#include <driver/gpio.h>
#include <esp_system.h>
#include <stdint.h>
#include <esp_sntp.h>
#include <esp_timer.h>

#define LED_PIN_1 12
#define LED_PIN_2 13
#define LED_PIN_3 11
#define BLINK_AMOUNT 10 
#define BLINK_PERIOD 10000
const size_t LAST_TOGGLE  = 0;

void loop1(void *tuggle_led) {
    size_t LAST_TOGGLE = 0;
    size_t BLINK_COUNT = 0;

    while (1) { 
        size_t CURRENT_TIME = esp_timer_get_time();
        gpio_set_level(LED_PIN_1, 0);
        gpio_set_level(LED_PIN_2, 0); 
        if (CURRENT_TIME - LAST_TOGGLE >= BLINK_PERIOD) { // did i set BLINK_PEROD to low?
            LAST_TOGGLE = CURRENT_TIME;
            gpio_set_level(LED_PIN_1, !LED_PIN_1); // look like this line didn't work.
            BLINK_COUNT++; // seem like it work.
            }
        else {
            gpio_set_level(LED_PIN_1, 0);
        }
        if(BLINK_COUNT >= BLINK_AMOUNT) {
            gpio_set_level(LED_PIN_3, !LED_PIN_3); // LED didn't on IDK why.
            gpio_set_level(LED_PIN_2, 1);// {  
            gpio_set_level(LED_PIN_1, 1);// this work.
            vTaskDelay(pdMS_TO_TICKS(3000));// }
            break;
        }
        
    }
}
void app_main() {
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_3, GPIO_MODE_OUTPUT);

    xTaskCreate(loop1, "blink_led1", 2048, NULL, 5, NULL);// this line helped by COPILOT.
}