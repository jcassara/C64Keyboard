#include "keystatereporter.h"
#include "const.h"
#include "cbmkeys.h"
#include "Keyboard.h"
#include "keymaps.h"
#include "timer.h"

/* Swapper state machine states */
typedef enum {
    kIdle,
    kWaitingForTimer,
    kSwapState
  } SwapperState;

/* Tracks time swapper keys are held down */
static Timer swapper_timer;

/* ReportKeyStateChange
 * Scans key state (pressed or released) for the column and row provided, reporting it to the USB keyboard module.
 */
void ReportKeyStateChange(uint8_t col_num, uint8_t row_num) {
    KeyState *ptr_key_state;
    if (col_num != kRestoreCol) {
        ptr_key_state = &key_states[col_num][row_num];
    } else {
        ptr_key_state = &restore_state;
    }
    if (ptr_key_state->current_state != ptr_key_state->last_state) {
#ifdef DEBUG
        char mess[255];
        sprintf(mess, "%c Col %d Row %d State %s", current_keymap[col_num][row_num], col_num, row_num, ptr_key_state->current_state ? "DOWN":"UP");
        Serial.println(mess);
#endif
        if (ptr_key_state->current_state) {
            Keyboard.press(current_keymap[col_num][row_num]);
        } else {
            Keyboard.release(current_keymap[col_num][row_num]);
        }
        ptr_key_state->last_state = ptr_key_state->current_state;
    }
}

/* ReportReleaseAllKeys
 * Commands the USB keyboard module to release all keys.
 */
void ReportReleseAllKeys(void) {
    Keyboard.releaseAll();
}

/* HandleModeSwapper
 * State machine for tracking when Commodore+Control key combo is depressed for
 * kSwapTimerMs time, changing between standard keyboard and joystick modes.
 */
void HandleModeSwapper(void) {

    // keyboard mode
    static bool is_joystick_mode = false;

    // combo press
    static SwapperState swapper_state = kIdle;

    switch (swapper_state) {
        case kIdle : {
            if (CheckSwapperStateChanged()) {
                swapper_state = kWaitingForTimer;
                TimerCreate(&swapper_timer, kSwapTimerMs);
            }
            break;
        }
        case kWaitingForTimer : {
            if (!CheckSwapperComboActive()) {
                TimerDisable(&swapper_timer);
                swapper_state = kIdle;
            } else {
                if (TimerIsDone(&swapper_timer)) {
                    swapper_state = kSwapState;
                    TimerDisable(&swapper_timer);
                    is_joystick_mode = !is_joystick_mode;
                }
            }
            break;
        }
        case kSwapState : {
            if (is_joystick_mode) {
                current_keymap = vice_pos_key_map_joy;
                analogWrite(kPowerLedArduinoPin, kLoLed);
                ReportReleseAllKeys();
            } else {
                current_keymap = vice_pos_key_map;
                analogWrite(kPowerLedArduinoPin, kHiLed);
                ReportReleseAllKeys();
            }
            swapper_state = kIdle;
            break;
        }
        default: {
        }
    }
}

/* HandleKeyStateChanges
 * Traverses the stored key states, reporting them to the USB keyboard module.
 */
void HandleKeyStateChanges(void) {
    for (uint8_t col_num = 0; col_num < kNumCols; col_num++) {
        for (uint8_t row_num = 0; row_num < kNumRows; row_num++) {
            ReportKeyStateChange(col_num, row_num);
        }
    }
    ReportKeyStateChange(kRestoreCol, 0);
}