#include "interrupts.h"
#include <stdio.h>

void interrupt_init(void) {
    printf("[INTERRUPT] Setting up interrupts...\n");
}

void enable_interrupts(void) {
    printf("[INTERRUPT] Enabling interrupts...\n");
}

void disable_interrupts(void) {
    printf("[INTERRUPT] Disabling interrupts...\n");
}

