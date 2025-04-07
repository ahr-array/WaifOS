#include <stdio.h>
#include "kernel.h"
#include "task.h"
#include "scheduler.h"
#include "interrupts.h"
#include "esp_timer.h"
#include "esp_err.h"
#include <stdio.h>

void task1() {
    while (1) {
        printf("🟢 Task 1 is running\n");
        for (volatile int i = 0; i < 10000000; i++); // Fake delay
    }
    task_yield();
}

void task2() {
    while (1) {
        printf("🔵 Task 2 is running\n");
        for (volatile int i = 0; i < 10000000; i++); // Fake delay
    }
    task_yield();
}


void app_main(void) {
    printf("\n==== WAIFOS OS Bootloader ====\n");
    printf("[Bootloader] Initializing Kernel...\n");

    kernel_init();  // Initialize task system and core scheduler

    printf("[Bootloader] Creating tasks...\n");
    create_task1(task1, 2048);
    create_task1(task2, 2048);

    printf("[Bootloader] Initializing Timer Interrupt...\n");
    init_timer();  // Set up timer for preemptive scheduling

    printf("[Bootloader] Starting Kernel Scheduler...\n");
    start_first_task();  // Begin task execution (does not return)

    printf("[Bootloader] Error: System should not reach this point!\n");
    while (1);  // Failsafe loop
}

