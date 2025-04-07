idf_component_register(SRCS "src/kernel.c" "src/memory.c" "src/task.c" "src/interrupts.c" "src/scheduler.c" "src/switch.S"
                       INCLUDE_DIRS "include"
                       REQUIRES driver
                       REQUIRES esp_timer)
