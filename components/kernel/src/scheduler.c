#include "task.h"
#include "scheduler.h"
#include <stdio.h>
#include <setjmp.h>

extern void yield();  // Implemented in your ISR

static jmp_buf main_context;

void scheduler_init() {
    printf("[Scheduler] Initializing scheduler environment...\n");

    // Reset current task index to invalid
    set_current_task_index(-1);

    // Optional: sanity check task count
    if (get_task_count() == 0) {
        printf("[Scheduler] Warning: No tasks created!\n");
    }

    // Future: initialize priority queues, sleeping task list, etc.
    // Example:
    // init_priority_queues();
    // init_sleeping_tasks();

    printf("[Scheduler] Scheduler ready.\n");
}

void scheduler_run(void) {
    // Start the first task (task 0)
    current_task_index = 0;
    if (setjmp(task_context[current_task_index]) == 0) {
        tasks[current_task_index].task_func();  // Run the task
    }

    // This loop ensures the scheduler continues running after each task yields.
    while (1) {
        task_yield();  // Switch to the next task
    }
}


void start_first_task() {
     volatile int i;
    for (i = 0; i < get_task_count(); i++) {
        set_current_task_index(i);
        task_t *task = get_task_by_index(i);
        if (!task) continue;

        if (setjmp(main_context) == 0) {
            if (setjmp(task->context) == 0) {
                asm volatile("mov sp, %0" :: "r"(task->stack + STACK_SIZE));
                task->state = TASK_RUNNING;
                task->entry();
                task->state = TASK_TERMINATED;
                yield();
            }
        }
    }
}

void schedule_next() {
    int current_index = get_current_task_index();
    int next = (current_index + 1) % get_task_count();

    for (int i = 0; i < get_task_count(); i++) {
        int idx = (next + i) % get_task_count();
        task_t *task = get_task_by_index(idx);
        if (!task) continue;

        if (task->state == TASK_READY || task->state == TASK_RUNNING) {
            if (setjmp(get_task_by_index(current_index)->context) == 0) {
                set_current_task_index(idx);
                longjmp(task->context, 1);
            }
        }
    }
}

