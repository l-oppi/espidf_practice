#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define ECHO_TEST_TXD (GPIO_NUM_1)
#define ECHO_TEST_RXD (GPIO_NUM_3)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define BUF_SIZE 1024

void echo_task(void *arg) {
    const int uart_num = UART_NUM_0;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    esp_err_t ret = uart_param_config(uart_num, &uart_config);
    if(ret != ESP_OK){
        ESP_LOGE("UART", "Failed to configure UART: %s", esp_err_to_name(ret));
        return;
    }
    uart_set_pin(uart_num, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);

    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while(1) {
        int len = uart_read_bytes(uart_num, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);
        if(len > 0) {
            uart_write_bytes(uart_num, (const char *) data, len);
        }
    }
}

void app_main(void)
{
    xTaskCreate(&echo_task, "uart_echo_task", 2048, NULL, 10, NULL);
}
