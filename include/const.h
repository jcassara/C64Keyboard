#ifndef CONST_H
#define CONST_H

#define kPowerLedArduinoPin 2

// Number of rows and cols for key scanning only
// NB - do not include RESTORE
#define kNumRows 8
#define kNumCols 8

// The column we're storing RESTORE key state struct
#define kRestoreCol kNumCols

#define kRestoreArduinoPin 22

// Number of reads a key state must maintain
// to eleminate bounce
#define kDebounceThreshold 50
#define kDebounceReset 0

// Where these keys exist in the matrix - for mode swap
#define kCbmKeyCol 0
#define kCbmKeyRow 5
#define kCtrlKeyCol 0
#define kCtrlKeyRow 2

// LED
#define kHiLed 100
#define kLoLed 10

#endif //CONST_H
