#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>

void switch_task(void);
void switch_task_asm(uint32_t *current_sp, uint32_t *next_sp);

#endif // SWITCH_H

