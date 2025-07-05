#ifndef CBMKEYS_H
#define CBMKEYS_H

#include <stdint.h>
#include <stdbool.h>
#include "const.h"

// Holds state for each key
typedef struct {
    bool current_state;
    bool last_state;
    bool last_read_state;
    uint8_t debounce_counter;
} KeyState;

extern KeyState key_states[kNumCols][kNumRows];
extern KeyState restore_state;

void ReadKeys(void);
void DebounceKeys(void);

#endif //CBMKEYS_H
