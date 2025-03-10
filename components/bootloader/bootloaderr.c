#include <stdio.h>
#include <esp_system.h>
#include "esp_log.h"
#include "driver/uart.h"

void uart_init() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);
    ESP_LOGI("Bootloader", "UART initialized.");
}

void bootloader_main() {
    // Initialize hardware
    ESP_LOGI("Bootloader", "Initializing hardware...");
    uart_init();

    // Load the kernel from flash
    ESP_LOGI("Bootloader", "Loading kernel...");
    void (*kernel_entry)() = (void (*)()) 0x40080000; // Kernel entry point
    kernel_entry(); // Jump to the kernel
}
