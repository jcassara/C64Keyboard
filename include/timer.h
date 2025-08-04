#ifndef timer_h
#define timer_h
#include <Arduino.h>
#include <stdbool.h>

typedef struct {
    bool is_enabled;
    bool is_done;
    uint64_t deadline_ms;
    uint64_t birthtime_ms;
} Timer;

bool TimerIsDone(Timer *timer);
void TimerCreate(Timer *timer, uint64_t deadline_ms);
void TimerReset(Timer *timer);
void TimerDisable(Timer *timer);

#endif /* timer_h */
