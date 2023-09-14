#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO_PIN 2

void blink_task(void *pvParameter) {
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);
    int gpio_value = 1;
    while(1) {
        gpio_value = !gpio_value;
        gpio_set_level(LED_GPIO_PIN, gpio_value);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
