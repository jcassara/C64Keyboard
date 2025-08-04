#include "keystatereporter.h"
#include "const.h"
#include "cbmkeys.h"
#include "Keyboard.h"
#include "keymaps.h"

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

void ReportReleseAllKeys(void) {
    Keyboard.releaseAll();
}