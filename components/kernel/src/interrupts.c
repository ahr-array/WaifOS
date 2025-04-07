#include "interrupts.h"
#include "scheduler.h"
#include <esp_timer.h>
#include "esp_attr.h"

#define TIMER_INTERVAL_MS 100

void IRAM_ATTR timer_callback(void* arg) {
    yield();
}

void init_timer() {
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_callback,
        .name = "waifos_timer"
    };

    esp_timer_handle_t timer;
    esp_timer_create(&timer_args, &timer);
    esp_timer_start_periodic(timer, TIMER_INTERVAL_MS * 1000);
}

// This is called inside the timer ISR
void yield() {
    schedule_next();
}
