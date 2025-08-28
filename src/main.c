#include <stdio.h>
#include <esp_log.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_task_wdt.h"

const char* TAG = "LED BLINKER";

#define BlinkAmount 10 
#define BLINK_PERIOD_MS 500

const gpio_num_t LED_PIN = GPIO_NUM_13;

void app_main() {

    
    uint64_t CURRENT_TIME = 0;
    uint64_t LAST_TOGGLE = 0;
    size_t BLINK_COUNT = 0;
    bool LEDSTATE = false;
   
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGI(TAG, "starting blinking...");

    while(true) {  
        CurrenTime = (uint64_t) (esp_timer_get_time() / 1000);
        ESP_LOGV(TAG, "Current time: %" PRIu64 " ms", CurrenTime);

        if (CurrenTime - LastToggle >= BLINK_PERIOD_MS) { 
            
            LastToggle = CurrenTime;
            
            if (LEDSTATE == false) { // when time has come if LED off set to on
                gpio_set_level(LED_PIN, LEDSTATE);
                BLINK_COUNT++;
                ESP_LOGD(TAG, "LED state: %d, counter %u", LEDSTATE, BLINK_COUNT);
            }

            else { // when time has come if LED on
                LEDState = false; // turn LEDState to off
                gpio_set_level(LED_PIN, LEDState); // set LED pin to off
                ESP_LOGD(TAG, "LED state: %d", LEDState);
            }

        }

        if(BlinkCount >= BlinkAmount) {
            break;
        }

        vTaskDelay(1);
    }

    ESP_LOGI(TAG, "Blinking done. Blinked %u times...", BlinkCount);
}
