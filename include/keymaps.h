#ifndef KEYMAPS_H
#define KEYMAPS_H
#include <cstdint>

#include "const.h"

extern const uint8_t vice_pos_key_map[kNumCols+1][kNumRows];
extern const uint8_t vice_pos_key_map_joy[kNumCols+1][kNumRows];
extern const uint8_t (*current_keymap)[kNumRows];

#endif //KEYMAPS_H
