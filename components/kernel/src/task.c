#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static task_t tasks[MAX_TASKS];
static int task_count = 0;
static int current_task_index = -1;

task_t* get_task_by_index(int index) {
    if (index >= 0 && index < MAX_TASKS) return &tasks[index];
    return NULL;
}

int get_task_count() {
    return task_count;
}

void set_current_task_index(int index) {
    current_task_index = index;
}

int get_current_task_index() {
    return current_task_index;
}


void task_yield(void) {
    // Save the current task's state using setjmp
    if (setjmp(task_context[current_task_index]) == 0) {
        // Move to the next task in the list
        current_task_index = (current_task_index + 1) % MAX_TASKS;

        // Restore the next task's state using longjmp
        longjmp(task_context[current_task_index], 1);
    }
}


// task_create should add tasks to the tasks array
void create_task(void (*entry_point)(void)) {
    if (get_task_count() < MAX_TASKS) {
        task_t *task = &tasks[get_task_count()];
        task->entry = entry_point;
        task->state = TASK_READY;
        task->stack = malloc(STACK_SIZE);  // Allocate stack for the task
        if (task->stack == NULL) {
            printf("[Scheduler] Error: Failed to allocate stack for new task\n");
            return;
        }

        // Set the context for the task (can use setjmp for task switching)
        if (setjmp(task->context) == 0) {
            // Save the context for the task at the entry point
            task->state = TASK_READY;
            task_count++;
        }
    } else {
        printf("[Scheduler] Error: Task array is full\n");
    }
}

void create_task1(void (*task_func)(void), uint32_t stack_size) {
    if (current_task_index >= MAX_TASKS - 1) {
        printf("Error: Max number of tasks reached.\n");
        return;
    }

    current_task_index++;

    // Allocate memory for task stack
    tasks[current_task_index].stack = (uint8_t *)malloc(stack_size);
    if (tasks[current_task_index].stack == NULL) {
        printf("Error: Stack allocation failed.\n");
        return;
    }

    tasks[current_task_index].stack_size = stack_size;
    tasks[current_task_index].task_func = task_func;
    tasks[current_task_index].state = TASK_READY;
}

