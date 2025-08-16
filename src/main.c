#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <esp_system.h>
#include <freertos/task.h>
#include <esp_timer.h>
#define LED_PIN_1 13
#define LED_PIN_2 12

int currentTime = 0;

void app_main() {}
    
    //set up GPIO pins for output
void setuo_gpio() {
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_2, GPIO_MODE_OUTPUT);
    
    }
//
void loop(void *pvParameter) {
    //counter until 10 seconds then reset
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    while(1) {
        if(currentTime >= 10 * 1000000) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);// 1 second delay    
            currentTime = 0; // Reset the counter?
            }
        else {
            gpio_set_level(LED_PIN, 0);
        }
    }
}
// Second task to blink LED_PIN_2 every second for 10 seconds
void loop2(void *pvParameter) {
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    while(1) {
        if (currentTime < 10 * 1000000) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 second delay
        }

        
    }
}
void start_task() {
    setuo_gpio();
    xTaskCreate(loop, "loop", 2048, (void *)LED_PIN_1, 5, NULL);
    xTaskCreate(loop, "loop2", 2048, (void *)LED_PIN_2, 5, NULL);
}