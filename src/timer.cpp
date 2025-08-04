#include "timer.h"
#include <Arduino.h>

bool TimerIsDone(Timer *timer) {
    static bool result;
    if (millis() >= (timer->birthtime_ms + timer->deadline_ms)) {
        timer->is_done = true;
        // timer is done if time elapsed
        result = (timer->is_done) && (timer->is_enabled);
        timer->is_enabled = false;
    } else {
        result = false;
    }
    return result;
}

void TimerCreate(Timer *timer, uint64_t deadline_ms) {
    timer->is_enabled = true;
    timer->is_done = false;
    timer->deadline_ms = deadline_ms;
    timer->birthtime_ms = millis();
}

void TimerReset(Timer *timer) {
    TimerCreate(timer, timer->deadline_ms);
}

void TimerDisable(Timer *timer) {
    timer->is_enabled = false;
}
