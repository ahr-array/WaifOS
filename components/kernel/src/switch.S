.global switch_task_asm

switch_task_asm:
    // Save current registers to the current task's stack
    s32i a2, a2, 0  // Save current stack pointer (SP)
    s32i a3, a3, 4  // Save current task's state (if needed)

    // Load the new task's stack pointer
    l32i a2, a3, 0  // Load new task's stack pointer (SP)
    l32i a3, a3, 4  // Load new task's state (if needed)

    // Return to the new task (context switch)
    ret.n

