#include <Keyboard.h>
#include "keymaps.h"

/* Map keys to expected keys on host that correspond to VICE's POSITIONAL keymap */
const uint8_t vice_pos_key_map[kNumCols+kRestoreColumn][kNumRows] = {
    { '1', '`', KEY_TAB, KEY_ESC, 0x20, KEY_LEFT_CTRL, 'q', '2' },
    { '3', 'w', 'a', KEY_LEFT_SHIFT, 'z', 's', 'e', '4' },
    { '5', 'r', 'd', 'x', 'c', 'f', 't', '6' },
    { '7', 'y', 'g', 'v', 'b', 'h', 'u', '8' },
    { '9', 'i', 'j', 'n', 'm', 'k', 'o', '0' },
    { '-', 'p', 'l', ',', '.', ';', '[', '=' },
    { KEY_END, ']', '\'', '/', KEY_RIGHT_SHIFT, KEY_PAGE_DOWN, '\\', KEY_HOME },
    { KEY_BACKSPACE, KEY_RETURN, KEY_RIGHT_ARROW , KEY_DOWN_ARROW, KEY_F1, KEY_F3, KEY_F5, KEY_F7 },
    { KEY_PAGE_UP, 0, 0, 0, 0, 0, 0, 0 }
};

/* Map keys to expected keys on host that correspond to VICE's Keyset Joystick keymap,
 * with additional POSITIONAL keys active for convienence.
 * WASD = Keypad North West South East
 * Spacebar = Fire 1
 * 0-9
 * +/-
 * Function Keys
 * Return
 * Right Shift
 * Cursor Keys
 * y/n
 * Return key
 * q
 * Run Stop/Restore
 */
const uint8_t vice_pos_key_map_joy[kNumCols+kRestoreColumn][kNumRows] = {
    { '1', 0, KEY_TAB, KEY_ESC, KEY_KP_0, KEY_LEFT_CTRL, 'q', '2' },
    { '3', KEY_KP_8, KEY_KP_4, 0, 0, KEY_KP_2, 0, '4' },
    { '5', 0, KEY_KP_6, 0, 0, 0, 0, '6' },
    { '7', 'y', 0, 0, 0, 0, 0, '8' },
    { '9', 0, 0, 'n', 0, 0, 0, '0' },
    { '-', 0, 0, 0, 0, 0, 0, '=' },
    { 0, 0, 0, 0, KEY_RIGHT_SHIFT, 0, 0, 0 },
    { 0, KEY_RETURN, KEY_RIGHT_ARROW , KEY_DOWN_ARROW, KEY_F1, KEY_F3, KEY_F5, KEY_F7 },
    { KEY_PAGE_UP, 0, 0, 0, 0, 0, 0, 0 }
};

// Keymap pointed to switches depending on mode we're in
const uint8_t (*current_keymap)[kNumRows] = vice_pos_key_map;