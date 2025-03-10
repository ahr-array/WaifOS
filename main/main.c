#include <stdio.h>
#include "kernel.h"
#include "task.h"

void task1(void) {
    while (1) {
        printf("Task 1 running...\n");
    }
}

void task2(void) {
    while (1) {
        printf("Task 2 running...\n");
    }
}

void app_main(void) {
    kernel_init();
    create_task(task1);
    create_task(task2);
    kernel_start();
}
