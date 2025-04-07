#include "kernel.h"
#include "scheduler.h"
#include "task.h"
#include "interrupts.h"
#include <stdio.h>

void kernel_init() {
    printf("[Kernel] Initializing WAIFOS...\n");
    scheduler_init();  // Setup the scheduler (timer interrupt)
}

void kernel_start() {
    printf("[Kernel] Starting OS...\n");
}

void kernel_panic(const char *message) {
    printf("[Kernel Panic] %s\n", message);
    while (1);  // Halt execution
}

