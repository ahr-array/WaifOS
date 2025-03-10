#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 4

typedef struct {
    uint32_t id;
    void (*entry)(void);
    uint32_t *stack_pointer;
} Task;

void task_init(void);
void create_task(void (*entry)(void));
void schedule(void);

#endif // TASK_H

