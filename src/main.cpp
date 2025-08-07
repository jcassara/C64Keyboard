#include <Arduino.h>
#include <string.h>
#include "cbmkeys.h"
#include "cbmpins.h"
#include "const.h"
#include "keymaps.h"
#include "keystatereporter.h"

/*MIT License
 * Copyright (c) 2025 Joe Cassara
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* DoPowerLedStartup
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

/* setup
 * Initializes the system
 */
void setup() {
  InitKeyStates();
  PinConfigurePins();
  DoPowerLedStartup();
#ifdef DEBUG
  Serial.begin(57600);
  Serial.println("READY");
#endif
}

/* loop
 * Superloop for scanning, debouncing, reporting, and handling mode swapper.
 */
void loop() {
  ReadKeys();
  DebounceKeys();
  HandleKeyStateChanges();
  HandleModeSwapper();
}