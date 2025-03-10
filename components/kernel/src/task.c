#include "task.h"
#include <stdio.h>

static Task task_list[MAX_TASKS];
static int current_task = -1;
static int task_count = 0;

void task_init(void) {
    printf("[TASK] Initializing task system...\n");
    task_count = 0;
}

void create_task(void (*entry)(void)) {
    if (task_count >= MAX_TASKS) {
        printf("[TASK ERROR] Max tasks reached!\n");
        return;
    }
    task_list[task_count].id = task_count;
    task_list[task_count].entry = entry;
    task_list[task_count].stack_pointer = NULL; // Simplified for now
    task_count++;
}

void schedule(void) {
    while (1) {
        if (task_count == 0) {
            printf("[SCHEDULER] No tasks to run\n");
            return;
        }
        current_task = (current_task + 1) % task_count;
        printf("[SCHEDULER] Switching to task %d\n", current_task);
        task_list[current_task].entry();
    }
}

