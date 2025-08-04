#include <Arduino.h>
#include <string.h>
#include "cbmkeys.h"
#include "cbmpins.h"
#include "const.h"
#include "keymaps.h"
#include "keystatereporter.h"
#include "timer.h"

Timer swapper_timer;

/*
 * DoPowerLedStartup
 * Fade the power LED with a small delay for the aesthetic
 */
void DoPowerLedStartup(void) {
  pinMode(kPowerLedArduinoPin, OUTPUT);
  for (uint32_t pwm=0; pwm < 255; pwm++) {
    analogWrite(kPowerLedArduinoPin, pwm);
    delay(5);
  }
  analogWrite(kPowerLedArduinoPin, kHiLed);
}

/*
 * setup
 * Initializes the system
 */
void setup() {
  InitKeyStates();
  PinConfigurePins();
  DoPowerLedStartup();
  Serial.begin(57600);
  Serial.println("READY");
}

typedef enum {
  kIdle,
  kWaitingForTimer,
  kSwapState
} SwapperState;

#define kSwapTimerMs 250
void HandleModeSwapper(void) {

  // keyboard mode
  static bool mode_state = false;

  // combo press
  static SwapperState swapper_state = kIdle;

  switch (swapper_state) {
    case kIdle : {
      if (CheckSwapperStateChanged()) {
        swapper_state = kWaitingForTimer;
        TimerCreate(&swapper_timer, kSwapTimerMs);
      }
      break;
    }
    case kWaitingForTimer : {
      if (!CheckSwapperComboActive()) {
        TimerReset(&swapper_timer);
        swapper_state = kIdle;
      } else {
        if (TimerIsDone(&swapper_timer)) {
          swapper_state = kSwapState;
          TimerDisable(&swapper_timer);
          mode_state = !mode_state;
        }
      }
      break;
    }
    case kSwapState : {
      if (mode_state) {
        current_keymap = vice_pos_key_map_joy;
        analogWrite(kPowerLedArduinoPin, kLoLed);
        ReportReleseAllKeys();
      } else {
        current_keymap = vice_pos_key_map;
        analogWrite(kPowerLedArduinoPin, kHiLed);
        ReportReleseAllKeys();
      }
      swapper_state = kIdle;
      break;
    }
    default: {
    }
  }
}

void HandleKeyStateChanges(void) {
  for (uint8_t col_num = 0; col_num < kNumCols; col_num++) {
    for (uint8_t row_num = 0; row_num < kNumRows; row_num++) {
      ReportKeyStateChange(col_num, row_num);
    }
  }
  ReportKeyStateChange(kRestoreCol, 0);
}

void loop() {
  ReadKeys();
  DebounceKeys();
  HandleKeyStateChanges();
  HandleModeSwapper();
}