#ifndef KEYSTATEREPORTER_H
#define KEYSTATEREPORTER_H

#include <stdint.h>

void ReportKeyStateChange(uint8_t col_num, uint8_t row_num);
void ReportReleseAllKeys(void);
void HandleModeSwapper(void);
void HandleKeyStateChanges(void);
#endif //KEYSTATEREPORTER_H
