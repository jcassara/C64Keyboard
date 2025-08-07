#include <Arduino.h>
#include <assert.h>
#include "cbmpins.h"
#include "const.h"

/* Map column and rows to CBM keyboard connector pin numbers
 * NB - These are not Arduino pins numbers
 */
static uint8_t col[] = {
    20, 19, 18, 17, 16, 15, 14, 13
  };

static uint8_t row[] = {
    12, 11, 10, 9, 8, 7, 6, 5
  };

/* PinGetCol
 * Returns the CBM keyboard pin number for the provided column value
 */
uint8_t PinGetCol(uint8_t col_num) {
    assert(col_num < kNumCols);
    return col[col_num];
}

/* PinGetRow
 * Returns the CBM keyboard pin number for the provided row value
 */
uint8_t PinGetRow(uint8_t row_num) {
    assert(row_num < kNumRows);
    return row[row_num];
}

/*P inCbmToArduino
 * Returns the calculated Arduino pin number from the provided CBM keyboard pin value */
uint8_t PinCbmToArduino(uint8_t strobe) {
    return (2 * strobe) + 13;
}

/* PinConfigurePins
 * Configure Arduino pins. Column selector pins are inputs so they can be used as HIGH-Z outputs.
 * Both are configured as PULL_UP to eliminate noise
 */
void PinConfigurePins(void) {
    uint8_t cbm_pin = 0;
    for (int pin = 0; pin < 8; pin++) {
        cbm_pin = PinCbmToArduino(row[pin]);
        pinMode(cbm_pin, INPUT_PULLUP);
        cbm_pin = PinCbmToArduino(col[pin]);
        pinMode(cbm_pin, INPUT_PULLUP);
    }
    pinMode(kRestoreArduinoPin, INPUT_PULLUP);
}

/* PinSetFloat
 * Sets the mode of the provided pin to High-Z
 */
void PinSetFloat(uint32_t pin) {
    pinMode(pin, INPUT_PULLUP);
}

/* PinSetLow
 * Sets the mode of the provided pin to LOW
 */
void PinSetLow(uint32_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

/* PinSetHigh
 * Sets the mode of the provided pin to HIGH
*/
void PinSetHigh(uint32_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
}