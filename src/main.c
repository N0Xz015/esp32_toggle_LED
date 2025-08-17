#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <esp_system.h>
#include <freertos/task.h>
#include <esp_timer.h>
#define LED_PIN_1 2
#define LED_PIN_2 1

int currentTime = 0;

void app_main() {}
    
//set up GPIO pins for output
void setuo_gpio() {
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_2, GPIO_MODE_OUTPUT);
    
    }

void loop1(void *pvParameter) {
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    while(1) {
        esp_timer_start_once(( {
            .callback = NULL,
            .name = "timer"
        }), 1000000); // 1 second timer
            
        if (currentTime <= 10 * 1000000)  {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 second delay
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 second delay
            currentTime += 1000000; // Increment the counter by 1 second
        }
        if (currentTime >= 1 * 1000000) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(10000 / portTICK_PERIOD_MS);// 10 second delay    
        }
    }
}
void loop2(void *pvParameter) {
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    while(1) {
        if (currentTime >= 1 * 100000) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 second delay
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 second delay
        }
    }
}
void start_task() {
    setuo_gpio();
    xTaskCreate(loop1, "loop", 2048, (void *)LED_PIN_1, 5, NULL);
    xTaskCreate(loop2, "loop2", 2048, (void *)LED_PIN_2, 5, NULL);
}