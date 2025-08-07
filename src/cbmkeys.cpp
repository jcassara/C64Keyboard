#include <Arduino.h>
#include <assert.h>
#include <stdint.h>
#include "const.h"
#include "cbmkeys.h"
#include "cbmpins.h"

static uint8_t keyboard_matrix[kNumCols];
static bool restore_read = false;

KeyState key_states[kNumCols][kNumRows];
KeyState restore_state;

/* PinReadRowsInColumn
 * Pulls the provided column number low and reads each row pin state,
 * storing the key states in a bitmat that is returned in the row_bitmap
 * pointer
 */
static void PinReadRowsInColumn(uint8_t colnum, uint8_t *row_bitmap) {
    assert(colnum < kNumCols);
    assert(row_bitmap != NULL);
    *row_bitmap = 0;
    uint8_t cbm_pin = PinCbmToArduino(PinGetCol(colnum));
    PinSetLow(cbm_pin);
    for (uint8_t rownum = 0; rownum < kNumRows; rownum++) {
        *row_bitmap |= (digitalRead(PinCbmToArduino(PinGetRow(rownum))) == LOW) << rownum;
    }
    PinSetFloat(cbm_pin);
}


/* InitKeyStates
 * Clears the keystates
 */
void InitKeyStates(void) {
    memset(key_states, 0, sizeof(key_states));
}

/* ReadKeys
 * Scans the keyboard matrix by column and row, including the RESTORE key
 */
void ReadKeys(void) {
    for (uint8_t col_num = 0; col_num < kNumCols; col_num++) {
        PinReadRowsInColumn(col_num, &keyboard_matrix[col_num]);
    }
    restore_read = digitalRead(kRestoreArduinoPin) == LOW;
}

/* DebounceKey
 * Debounces the key readings at the provided column and row.
 * If the key at that position in the keyboard maxtrix has maintained
 * its state (pressed or released) for kDebounceThreshold number of
 * iterations, that state is steady and is reported in the
 * keystates matrix. Otherwise, the state is not yet steady.
 */
static void DebounceKey(uint8_t col_num, uint8_t row_num) {
    bool key_reading = false; // false = released, true = pressed
    KeyState *ptr_key_state;
    if (col_num != kRestoreCol) {
        key_reading = keyboard_matrix[col_num] & (1 << row_num);
        ptr_key_state = &key_states[col_num][row_num];
    } else {
        key_reading = restore_read;
        ptr_key_state = &restore_state;
    }

    if (key_reading == ptr_key_state->last_read_state) {
        ptr_key_state->debounce_counter++;
        if (ptr_key_state->debounce_counter >= kDebounceThreshold) {
            ptr_key_state->current_state = key_reading;
            ptr_key_state->debounce_counter = kDebounceThreshold;
        }
    } else {
        ptr_key_state->debounce_counter = kDebounceReset;
    }
    ptr_key_state->last_read_state = key_reading;
}

/* DebounceKeys
 * Debounces all keys in the keystates, called for each row individually for
 * timing.
 */
void DebounceKeys(void) {
    for (uint8_t col_num = 0; col_num < kNumCols; col_num++) {
        DebounceKey(col_num, 0);
        DebounceKey(col_num, 1);
        DebounceKey(col_num, 2);
        DebounceKey(col_num, 3);
        DebounceKey(col_num, 4);
        DebounceKey(col_num, 5);
        DebounceKey(col_num, 6);
        DebounceKey(col_num, 7);
        DebounceKey(kRestoreCol, 0);
    }
}

/* CheckSwapperComboActive
 * Returns true if both the Commodore and CTRL keys are depressed.
 */
bool CheckSwapperComboActive(void) {
    return key_states[kCtrlKeyCol][kCtrlKeyRow].current_state && key_states[kCbmKeyCol][kCbmKeyRow].current_state;
}

/* CheckSwapperStateChanged
 * Reports leading edge trigger of swapper trigger
 */
bool CheckSwapperStateChanged(void) {
    static bool swapper_combo = false;
    static bool last_swapper_combo = false;
    static bool leading_edge_trigger = false;
    swapper_combo = CheckSwapperComboActive();
    leading_edge_trigger =  (swapper_combo && !last_swapper_combo);
    last_swapper_combo = swapper_combo;
    return leading_edge_trigger;
}