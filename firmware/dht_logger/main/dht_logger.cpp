#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "rom/ets_sys.h" 

static const char *TAG = "ROCKET_TELEMETRY";

// Change this to the pin you actually used on your breadboard!
#define DHT_GPIO GPIO_NUM_32 

// This block tells the ESP-IDF (which is C) how to find our C++ function
extern "C" {
    void app_main(void);
}

void app_main(void) {
    ESP_LOGI(TAG, "Starting Month 1: DHT11 Handshake Test...");
    
    while (1) {
        // Step 1: Initialize the pin as Output to send the "Wake up" signal
        gpio_reset_pin(DHT_GPIO);
        gpio_set_direction(DHT_GPIO, GPIO_MODE_OUTPUT);

        // Step 2: Send Start Signal (Pull LOW for 20ms)
        gpio_set_level(DHT_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(20)); 
        
        // Step 3: Release the line (Pull HIGH) and wait for sensor
        gpio_set_level(DHT_GPIO, 1);
        ets_delay_us(40);
        
        // Step 4: Switch to Input to listen for the sensor's response
        gpio_set_direction(DHT_GPIO, GPIO_MODE_INPUT);
        ets_delay_us(10); 

        // Step 5: The Handshake Check
        // If the sensor is alive, it will pull the line LOW to acknowledge us.
        if (gpio_get_level(DHT_GPIO) == 0) {
            ESP_LOGI(TAG, "--- SUCCESS: SENSOR IS ALIVE! ---");
        } else {
            ESP_LOGE(TAG, "--- FAILURE: NO RESPONSE ---");
            ESP_LOGI(TAG, "Troubleshoot: Check your GND/3.3V and signal pin.");
        }

        // Wait 3 seconds before the next telemetry pulse
        vTaskDelay(pdMS_TO_TICKS(3000)); 
    }
}
