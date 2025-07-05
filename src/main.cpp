#include <Arduino.h>
#include <string.h>
#include "cbmkeys.h"
#include "cbmpins.h"
#include "const.h"
#include "keymaps.h"
#include "../include/keystatereporter.h"

void setup() {
  memset(key_states, 0, sizeof(key_states));
  PinConfigurePins();
  #ifdef DEBUG
  Serial.begin(57600);
  Serial.println("READY");
  #endif
  // Illuminate LED slowly for that nice warm feeling...
  pinMode(kPowerLedArduinoPin, OUTPUT);
  for (uint32_t pwm=0; pwm < 255; pwm++) {
    analogWrite(kPowerLedArduinoPin, pwm);
    delay(5);
  }
  digitalWrite(kPowerLedArduinoPin, HIGH);
}

void HandleKeyStateChanges(void) {
  static bool swapper_combo = false;
  static bool last_swapper_combo = false;
  static bool swapper_state = false;

  for (uint8_t col_num = 0; col_num < kNumCols; col_num++) {
    for (uint8_t row_num = 0; row_num < kNumRows; row_num++) {
      ReportKeyStateChange(col_num, row_num);
    }
  }

  ReportKeyStateChange(kRestoreCol, 0);

  swapper_combo = key_states[kCtrlKeyCol][kCtrlKeyRow].current_state && key_states[kCbmKeyCol][kCbmKeyRow].current_state;
  if (swapper_combo && !last_swapper_combo) {
    swapper_state = !swapper_state; // toggle
    analogWrite(2, swapper_state ? 10 : 255);
    if (swapper_state) {
      current_keymap = vice_pos_key_map_joy;
    } else {
      current_keymap = vice_pos_key_map;
    }
  }

  last_swapper_combo = swapper_combo;

}

void loop() {
  ReadKeys();
  DebounceKeys();
  HandleKeyStateChanges();
}