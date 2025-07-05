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

void ReadKeys(void) {
    for (uint8_t col_num = 0; col_num < kNumCols; col_num++) {
        PinReadRowsInColumn(col_num, &keyboard_matrix[col_num]);
    }
    restore_read = digitalRead(kRestoreArduinoPin) == LOW;
}

static void DebounceKey(uint8_t col_num, uint8_t row_num) {
    bool key_reading = false;
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
            if (key_reading != ptr_key_state->current_state) {
                ptr_key_state->current_state = key_reading;
            }
            ptr_key_state->debounce_counter = kDebounceThreshold;
        }
    } else {
        ptr_key_state->debounce_counter = kDebounceReset;
    }
    ptr_key_state->last_read_state = key_reading;
}

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