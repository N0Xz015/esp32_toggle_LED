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

    // i got you
    uint64_t CurrenTime = 0;       
    uint64_t LastToggle = 0; 
    size_t BlinkCount = 0;          
    bool LEDState = false;           
   
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGI(TAG, "starting blinking...");

    while(true) {  
        CurrenTime = (uint64_t) (esp_timer_get_time() / 1000);
        ESP_LOGV(TAG, "Current time: %" PRIu64 " ms", CurrenTime);

        if (CurrenTime - LastToggle >= BLINK_PERIOD_MS) { 
            
            LastToggle = CurrenTime;
            
            if (LEDState == false) { // when time has come if LED off
                LEDState = true; // so this line will change LEDState to on
                gpio_set_level(LED_PIN, LEDState); // this line will set LED pin to on from upper line
                BlinkCount++;
                ESP_LOGD(TAG, "LED state: %d, counter: %u", LEDState, BlinkCount);
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
