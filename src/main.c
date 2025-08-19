#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <esp_system.h>
#include <freertos/task.h>

#define LED_PIN_1 12
#define LED_PIN_2 13

//set up GPIO pins for output
void setuo_gpio() {
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_2, GPIO_MODE_OUTPUT);
}

void loop1(void *pvParameter) {
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    int looped = 0; 
    while(1) {
        if (looped < 10) {
            gpio_set_level(LED_PIN_2, 0);
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        else {
            gpio_set_level(LED_PIN_2, 1);
            gpio_set_level(LED_PIN_2, LED_PIN_1 ? 1 : 1);
            vTaskDelay(pdMS_TO_TICKS(5000));
            looped = 0; // Reset loop count
        }
    looped += 1 ;
    }
}
void app_main() {
    setuo_gpio(); // Set up GPIO pins for output
    xTaskCreate(loop1, "loop1", 2048, (void *)LED_PIN_1, 5, NULL); 
}
    
