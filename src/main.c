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
void loop(void *pvParameter) {
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    int looped = 0; 
    while(1) {
        if (currentTime < 10) {
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(500/ portTICK_PERIOD_MS);// 0.5 second delay
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS); // 0.5 second
        }
        
    currentTime += 1; // Increment current time by 1 second
        
    }
}
void loop2(void *pvParameter) {
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    extern int currentTime;
    while(1) {
        if (currentTime >= 10) { // Check if 10 seconds have passed
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(5000 / portTICK_PERIOD_MS); // 5 second delay
            currentTime = 0; // Reset current time
        }
    }
}
void app_main() {
    setuo_gpio(); // Set up GPIO pins for output
    xTaskCreate(loop1, "loop1", 2048, (void *)LED_PIN_1, 5, NULL); 
    xTaskCreate(loop2, "loop2", 2048, (void *)LED_PIN_2, 5, NULL); 
}
    