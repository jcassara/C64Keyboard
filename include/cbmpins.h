#ifndef CBMPINS_H
#define CBMPINS_H

#include <stdint.h>

void PinConfigurePins(void);
void PinSetFloat(uint32_t pin);
void PinSetLow(uint32_t pin);
void PinSetHigh(uint32_t pin);
uint8_t PinCbmToArduino(uint8_t strobe);
uint8_t PinGetCol(uint8_t col_num);
uint8_t PinGetRow(uint8_t row_num);
#endif //CBMPINS_H
