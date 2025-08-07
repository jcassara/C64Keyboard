# C64Keyboard
A PlatformIO project for the Arduino Due board, enabling the use of a Commodore 64 keyboard matrix as a USB keyboard for the VICE emulator. VICE must be configured to use positional keymapping. 

Holding the Commodore + CTRL keys for 250ms will place change to joystick mode, allowing for the WASD+Space keys to be used as a keyset joystick. The same key combination will return to keyboard mode. The LED will dim when in joystick mode.
