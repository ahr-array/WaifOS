#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void memory_init(void) {
    printf("[MEMORY] Initializing memory system...\n");
}

void *kmalloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        printf("[MEMORY ERROR] Allocation failed\n");
    }
    return ptr;
}

void kfree(void *ptr) {
    free(ptr);
}

