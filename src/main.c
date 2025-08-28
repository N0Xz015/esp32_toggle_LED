#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_task_wdt.h"

const char* TAG = "LED BLINKER";

#define BLINK_AMOUNT 10 
#define BLINK_PERIOD_MS 500

const gpio_num_t LED_PIN = GPIO_NUM_13;

void app_main() {

    /* CONST_ARE_UPCASE but regular variables areCamelCase - why always yell? */
    uint64_t CURRENT_TIME = 0;       /* currentTime */
    uint64_t LAST_TOGGLE = 0;        /* lastToggle */   
    size_t BLINK_COUNT = 0;          /* blinkCounter */
    bool LEDSTATE = false;           /* well, I guess you got it :) */
   
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGI(TAG, "starting blinking...");

    while(true) {  
        CURRENT_TIME = (uint64_t) (esp_timer_get_time() / 1000);
        ESP_LOGV(TAG, "Current time: %" PRIu64 "ms", CURRENT_TIME);

        if (CURRENT_TIME - LAST_TOGGLE >= BLINK_PERIOD_MS) { 
            
            LAST_TOGGLE = CURRENT_TIME;
            
            if (LEDSTATE == false) { // when time has come if LED off set to on /* That means the state is false (there is the value '0' written now) */ 
                gpio_set_level(LED_PIN, LEDSTATE); /* So, we write that '0' into the LED GPIO, setting it to OFF, means no change */
                BLINK_COUNT++;
                ESP_LOGD(TAG, "LED state: %d, counter %u", LEDSTATE, BLINK_COUNT);
            }

            else { // when time has come if LED on turn it off
                gpio_set_level(LED_PIN, false);
                ESP_LOGD(TAG, "LED state: %d", LEDSTATE);
            }

        }

        if(BLINK_COUNT >= BLINK_AMOUNT) {
            gpio_set_level(LED_PIN, 1);
            break;
        }

        vTaskDelay(5);
    }

    ESP_LOGI(TAG, "Blinking done. Blinked %u times...", BLINK_COUNT);
}
