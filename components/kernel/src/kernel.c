#include "kernel.h"
#include "memory.h"
#include "task.h"
#include "interrupts.h"
#include <stdio.h>

void kernel_init(void) {
    printf("[KERNEL] Initializing...\n");
    memory_init();
    task_init();
    interrupt_init();
}

void kernel_start(void) {
    printf("[KERNEL] Starting...\n");
    schedule();  // Start the task scheduler
}

void kernel_panic(const char *message) {
    printf("[KERNEL PANIC] %s\n", message);
    while (1);  // Halt system
}
