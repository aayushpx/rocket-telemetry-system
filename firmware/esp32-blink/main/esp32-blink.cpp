#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "soc/gpio_num.h"

#define BLINK_GPIO GPIO_NUM_2 // define LED pin
static const char *TAG = "BLINK"; // label for debugging

extern "C" void app_main(void)
{
    gpio_reset_pin(BLINK_GPIO); // makes sure pin is in default state
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT); // set pin to output
    while (true)
    {
        gpio_set_level(BLINK_GPIO, 1); // set output voltage HIGH
        ESP_LOGI(TAG, "LED ON"); // log for on state
        vTaskDelay(100 / portTICK_PERIOD_MS); // wait 5000ms=5state 
                        // portTICK converts ms into ticks 
        gpio_set_level(BLINK_GPIO, 0); // set output volt OFF
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(1900 / portTICK_PERIOD_MS); // wait 5s
    }
}
