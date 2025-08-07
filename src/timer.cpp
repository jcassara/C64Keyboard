#include "timer.h"
#include <Arduino.h>

/* TimerIsDone
 * Reports true if an enabled timer has reached its deadline
 */
bool TimerIsDone(Timer *timer) {
    static bool result;
    if (millis() >= (timer->birthtime_ms + timer->deadline_ms)) {
        timer->is_done = true;
        result = (timer->is_done) && (timer->is_enabled);
        timer->is_enabled = false;
    } else {
        result = false;
    }
    return result;
}

/* TimerCreate
 * Creates a timer that expires at the provided deadline in ms
 */
void TimerCreate(Timer *timer, uint64_t deadline_ms) {
    timer->is_enabled = true;
    timer->is_done = false;
    timer->deadline_ms = deadline_ms;
    timer->birthtime_ms = millis();
}

/* TimerReset
 * Resets a timer to its previous deadline
 */
void TimerReset(Timer *timer) {
    TimerCreate(timer, timer->deadline_ms);
}

/* TimerDisable
 * Sets a timer as disabled
 */
void TimerDisable(Timer *timer) {
    timer->is_enabled = false;
}
