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
   
void loop(void *pvParameter) {
    //counter until 10 seconds then reset
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    while(currentTime < 10 * 1000000) {
        if(currentTime >= 10 * 1000000) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(3000 / portTICK_PERIOD_MS); // 3 seconds delay            
            currentTime = 0; // Reset the counter
            }
            else {
            gpio_set_level(LED_PIN, 0);
            }
    }
}