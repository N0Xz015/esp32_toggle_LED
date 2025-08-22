#include <freertos/FreeRTOS.h>
#include <esp_system.h>
#include <freertos/task.h>

#define LED_PIN_1 12



//set up GPIO pins for output
void setuo_gpio() {     /* A typo? :) */
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    
}

/* This function is a FreeRTOS task created from app_main().
 * For such a small program, we could also skip the task and put
 * everything directly into app_main(): 
 *   - First do the setup (configure GPIOs, etc.)
 *   - Then run the infinite while(1) loop with the LED logic
 * Using a task is more flexible, but both approaches work.
 */
void loop1(void *pvParameter) {
    
    /* - Casting from void*, wow! Let's explore this topic - check what casting in C is, will you? */
    gpio_num_t LED_PIN = (gpio_num_t)pvParameter;
    
    /*   - For positive values it's best to use unsigned types (uint8_t, uint16_t, uint32_t).
     *     When counting items/iterations, size_t is often a good choice since it clearly means "counter of things".
     */
    int currentTime = 0;
    
    while(1) {
        if (currentTime < 10) {
            gpio_set_level(LED_PIN, 1);
            
            /* Prefer pdMS_TO_TICKS(500) instead of 500/portTICK_PERIOD_MS.
             * It's clearer and safer across FreeRTOS configs.
             */
            vTaskDelay(500/ portTICK_PERIOD_MS);// 0.5 second delay
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS); // 0.5 second
        }
        if (currentTime >= 10 ) { // Check if 10 seconds have passed
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(5000 / portTICK_PERIOD_MS); // 5 second delay
            currentTime = 0; // Reset current time
            }

    /* The name currentTime is misleading — it's counting loop iterations, not real time.
     * Variable names should answer "What is stored here?" A better name could be iterationCount or blinkCounter.
     */
    currentTime += 1; // Increment current time by 1 second
        
    }
}

void app_main() {
    setuo_gpio(); // Set up GPIO pins for output
    xTaskCreate(loop1, "loop1", 2048, (void *)LED_PIN_1, 5, NULL); // Create task for LED_PIN_1
}
    
