#include <Arduino.h>
#include "SapienSignal.h"

/**
 * Establish the pins. dataPin and clockPin are required
 * markPin is for enveloping the signal for debugging. 
 * clockPin is equally redundant. We only use an async dataPin
 **/
SapienSignal::SapienSignal(uint8_t dataPin, uint8_t markPin) {
        this->dataPin = dataPin;
        this->markPin = markPin;
    }

void SapienSignal::begin() {
        pinMode(dataPin, OUTPUT);
        digitalWrite(dataPin, HIGH);

        if (markPin >= 0) {
            // drop the debugging mark pin and flash it.
            pinMode(markPin, OUTPUT);
            digitalWrite(markPin, LOW);
            }
    }

void SapienSignal::shiftOut(uint8_t val) {
#if defined(__AVR_ATtiny85__)
        const int BASIC_CLOCK = 380; // microseconds 1/1200s = 833 but a scope sez it should be 360 for an attiny85
#else
        const int BASIC_CLOCK = 780; // microseconds 1/1200s = 833 but a scope sez it should be 780 for an uno
#endif
        // flag the start of clocking
        if (markPin >= 0) digitalWrite(markPin, HIGH);
        // here we implement the sequence sending
        // START SEQUENCE
        digitalWrite(dataPin, LOW);
        delayMicroseconds(8*BASIC_CLOCK);
        digitalWrite(dataPin, HIGH);

        // loop over data
    	for (uint8_t i = 0; i < 8; i++)  {
            if ((val & 0x80) == 0) {
                digitalWrite(dataPin, HIGH);
                delayMicroseconds(1*BASIC_CLOCK);
                digitalWrite(dataPin, LOW);
                delayMicroseconds(1*BASIC_CLOCK);
            }
            else {
                digitalWrite(dataPin, HIGH);
                delayMicroseconds(4*BASIC_CLOCK);
                digitalWrite(dataPin, LOW);
                delayMicroseconds(1*BASIC_CLOCK);
            }
			val <<= 1;
            }
        digitalWrite(dataPin, HIGH);

        // flag the end of clocking
        if (markPin >= 0) digitalWrite(markPin, LOW);
    }
