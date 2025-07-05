#include <Arduino.h>
#include <assert.h>
#include "cbmpins.h"
#include "const.h"

// Maps cols and rows to CBM keyboard connector pins
// NB - These are not Arduino pin numbers
static uint8_t col[] = {
    20, 19, 18, 17, 16, 15, 14, 13
  };

static uint8_t row[] = {
    12, 11, 10, 9, 8, 7, 6, 5
  };

uint8_t PinGetCol(uint8_t col_num) {
    assert(col_num < kNumCols);
    return col[col_num];
}

uint8_t PinGetRow(uint8_t row_num) {
    assert(row_num < kNumRows);
    return row[row_num];
}

// Convert CBM keyboard connector pin number to Arduino pin number
uint8_t PinCbmToArduino(uint8_t strobe) {
    return (2 * strobe) + 13;
}

void PinConfigurePins(void) {
    uint8_t cbm_pin = 0;
    // Configure Arduino pins
    // Col selector pins are inputs so they can be used as HIGH-Z outputs
    // Both PULL_IP to eliminate noise
    for (int pin = 0; pin < 8; pin++) {
        cbm_pin = PinCbmToArduino(row[pin]);
        pinMode(cbm_pin, INPUT_PULLUP);
        cbm_pin = PinCbmToArduino(col[pin]);
        pinMode(cbm_pin, INPUT_PULLUP);
    }
    pinMode(kRestoreArduinoPin, INPUT_PULLUP);
}

void PinSetFloat(uint32_t pin) {
    pinMode(pin, INPUT_PULLUP);
}

void PinSetLow(uint32_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void PinSetHigh(uint32_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
}