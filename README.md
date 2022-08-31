# digitalWriteFast
**This is a fork of the subtree https://github.com/watterott/Arduino-Libs/tree/master/digitalWriteFast.**

Arduino library for faster `digitalWrite()` using direct port manipulation and macro for ease in pin assignments **for constant pin numbers**. 
It also provides faster `pinMode()` and `digitalRead()` functions as well as it adds a digitalToggleFast() function.

**If pin number is no compile time constant, or the platform is not supported, then the regular Arduino functions `digitalWrite()` etc. are called.**
- Use '#define pinNum 10' instead of `int pinNum = 10;`
- Use 'const int pinNum 10' instead of `int pinNum = 10;`

[![License: BSD-3-Clause](https://img.shields.io/static/v1?label=license&message=BSD-3-Clause&color=blue)](https://opensource.org/licenses/BSD-3-Clause)
[![Installation instructions](https://www.ardu-badge.com/badge/digitatWriteFast.svg?)](https://www.ardu-badge.com/digitatWriteFast)
[![Commits since latest](https://img.shields.io/github/commits-since/ArminJo/digitatWriteFast/latest)](https://github.com/ArminJo/digitatWriteFast/commits/master)
[![Build Status](https://github.com/ArminJo/digitatWriteFast/workflows/LibraryBuild/badge.svg)](https://github.com/ArminJo/digitatWriteFast/actions)
![Hit Counter](https://visitor-badge.laobi.icu/badge?page_id=ArminJo_digitatWriteFast)


# Speed
For a 16 MHz Uno digitalWrite() is speed up from 5.8 µs to 125 ns, able to generate a 4 MHz signal instead of 86 kHz.
More info in: [/NOTES/NOTES.md](https://github.com/NicksonYap/digitalWriteFast/blob/master/NOTES/NOTES.md)

# Usage
Include the library:
`#include <digitalWriteFast.h>`

Macro definitions:
- `digitalWriteFast(pinNum, state)` (sets or clears pin/port faster) 
- `pinModeFast(pinNum, mode)` (sets pin/port as input or output faster)
- `digitalReadFast(pinNum)`(reads the state of pin/port faster) 
- `digitalToggleFast(pinNum)`(toggles the state of pin/port faster)

Parameters:
* `pinNum` is the number written on the Arduino board.
* `state` is weather pin is to be set `HIGH` or `LOW`
* `mode` is weather pin is to be set `INPUT` or `OUTPUT` or `INPUT_PULLUP`

# Example
This is the waveform generated with the Timing example.
![Timing example signal](https://github.com/ArminJo/digitalWriteFast/blob/master/pictures/DigitalWriteFastExample.bmp)

# Detection
Defining `THROW_ERROR_IF_NOT_FAST` would cause the macro to return an error during compilation, if the parameter is a variable and thus regular digital* functions must be called.
This notifies the programmer the specific area where code is still slow.

# Compatibility
* Arduino Uno, Nano etc.
* Arduino Leonardo
* Arduino Mega
* Arduino with ATmega644 or Atmega644P chip
* Arduino with ATmega4809 chip
* Arduino with ATtiny chip


# Revision History
### Version 1.1.0
- Added TEENSYDUINO support.
- Added THROW_ERROR_IF_NOT_FAST functionality.
- Removed unnecessary compare `> 0`.
- Added Guard `&& defined(__digitalPinToPINReg)` etc.
- Changed `ifndef` to `if !defined()`.

# Reference
This documentation is based on https://github.com/NicksonYap/digitalWriteFast/

