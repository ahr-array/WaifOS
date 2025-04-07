#ifndef TASK_H
#define TASK_H

#include <setjmp.h>
#include <stdint.h>

#define MAX_TASKS  4
#define STACK_SIZE 4096

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_TERMINATED
} task_state_t;

typedef struct task {
    int id;
    jmp_buf context;
    task_state_t state;
    void (*entry)(void);
    uint8_t *stack;
} task_t;

void create_task(void (*func)(void));
void create_task1(void (*task_func)(void), uint32_t stack_size)
task_t* get_task_by_index(int index);
int get_task_count();
void set_current_task_index(int index);
int get_current_task_index();
void task_yield(void);

#endif
