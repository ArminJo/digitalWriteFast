/*
 * Timing.ino
 *
 * digitalWriteFast example for boards with AVR microcontrollers (Arduino Uno, Leonardo, Mega etc.).
 *
 *  This file is part of digitalWriteFast https://github.com/ArminJo/digitalWriteFast.
 *
 ************************************************************************************
 * BSD 3-Clause License (https://opensource.org/licenses/BSD-3-Clause)
 *
 * Copyright (c) 2011-2020 Watterott electronic (www.watterott.com)
 * Copyright (c) 2020-2022 Armin Joachimsmeyer et al.
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * - Neither the name of the copyright holders nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************
 */

#include <Arduino.h>

//#define THROW_ERROR_IF_NOT_FAST // Activate this to detect where ...Fast() functions are called with NON constant parameters and are therefore still slow.
#include <digitalWriteFast.h>

#ifndef _NOP // required for some non Arduino cores
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

#define PIN 10

void setup() {
    int tConstantPinNumber = 0;

    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__));
    Serial.println(
            F(
                    "Generate 4 fast pulses with digitalWriteFast(), digitalToggleFast(), digitalReadFast() and then 4 slow pulses using plain digitalWrite()"));

    // set pin mode OUTPUT for pin PIN
    pinModeFast(PIN, OUTPUT);

    tConstantPinNumber = 9;
    // the compiler detects that this is a constant here and uses the fast command.
    digitalWriteFast(tConstantPinNumber, HIGH);

    // Here we have a fallback to the slow Arduino functions, because the compiler assumes, that tDynamicPinNumber is not a constant.
    // If THROW_ERROR_IF_NOT_FAST is defined above, this will lead to a compile time error showing the line of the statement.
    volatile int tDynamicPinNumber = 9;
    pinModeFast(tDynamicPinNumber, OUTPUT); // Here tDynamicPinNumber is not constant and therefore pinMode() is called.
    digitalToggleFast(tDynamicPinNumber); // Here tDynamicPinNumber is not constant and therefore digitalWrite(digitalRead()) is called.
    digitalWriteFast(tDynamicPinNumber, HIGH); // Here tDynamicPinNumber is not constant and therefore digitalWrite() is called.
    digitalReadFast(tDynamicPinNumber); // Here tDynamicPinNumber is not constant and therefore digitalRead() is called.
}

void loop() {
    // Generate 5 fast HIGH pulses (4 MHz @ 16 MHz Uno)
    digitalWriteFast(PIN, HIGH);
    digitalWriteFast(PIN, LOW);
    digitalWriteFast(PIN, HIGH);
    digitalWriteFast(PIN, LOW);
    digitalWriteFast(PIN, HIGH);
    digitalWriteFast(PIN, LOW);
    digitalWriteFast(PIN, HIGH);
    digitalWriteFast(PIN, LOW);

    delayMicroseconds(2);

    // and now again 5 fast pulses (4 MHz)
    digitalToggleFast(PIN); // HIGH
    digitalToggleFast(PIN);
    digitalToggleFast(PIN);
    digitalToggleFast(PIN);
    digitalToggleFast(PIN);
    digitalToggleFast(PIN);
    digitalToggleFast(PIN); // HIGH
    digitalToggleFast(PIN); // LOW

    delayMicroseconds(2);

    // Demonstrate how digitalReadFast in test generates SBIC commands (Skip if Bit in I/O Register is Cleared).
    // This additional check results in a only 2 times slower frequency (2 MHz)!
    //
    // Keep in mind that you cannot test with (digitalReadFast(PIN) == LOW (or HIGH)) immediately after digitalWriteFast(PIN,X)!
    // You must at least insert a nop instruction to get the desired behavior.
    if (digitalReadFast(PIN) == LOW) { digitalWriteFast(PIN, HIGH); }
    _NOP();
    if (digitalReadFast(PIN) == HIGH) { digitalWriteFast(PIN, LOW); }
    _NOP();
    if (digitalReadFast(PIN) == LOW) { digitalWriteFast(PIN, HIGH); }
    _NOP();
    if (digitalReadFast(PIN) == HIGH) { digitalWriteFast(PIN, LOW); }
    _NOP();
    if (digitalReadFast(PIN) == LOW) { digitalWriteFast(PIN, HIGH); }
    _NOP();
    if (digitalReadFast(PIN) == HIGH) { digitalWriteFast(PIN, LOW); }
    _NOP();
    if (digitalReadFast(PIN) == LOW) { digitalWriteFast(PIN, HIGH); }
    _NOP();
    if (digitalReadFast(PIN) == HIGH) { digitalWriteFast(PIN, LOW); }

    delayMicroseconds(2);

    // Now generate 5 slow HIGH pulses (86 kHz @ 16 MHz Uno)
    digitalWrite(PIN, HIGH);
    digitalWrite(PIN, LOW);
    digitalWrite(PIN, HIGH);
    digitalWrite(PIN, LOW);
    digitalWrite(PIN, HIGH);
    digitalWrite(PIN, LOW);
    digitalWrite(PIN, HIGH);
    digitalWrite(PIN, LOW);

    delayMicroseconds(50);
}
