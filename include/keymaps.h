#ifndef KEYMAPS_H
#define KEYMAPS_H
#include <cstdint>

#include "const.h"

// RESTORE key is not part of key scanning
#define kRestoreColumn 1

extern const uint8_t vice_pos_key_map[kNumCols+kRestoreColumn][kNumRows];
extern const uint8_t vice_pos_key_map_joy[kNumCols+kRestoreColumn][kNumRows];
extern const uint8_t (*current_keymap)[kNumRows];

#endif //KEYMAPS_H
