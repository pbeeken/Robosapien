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
        pinMode(markPin, OUTPUT);
        pinMode(dataPin, OUTPUT);

        digitalWrite(markPin, LOW);
        digitalWrite(dataPin, HIGH);
    }

void SapienSignal::shiftOut(uint8_t val) {
        const int BASIC_CLOCK = 833; // microseconds 
        // flag the start of clocking
        if ( markPin != 0 ) digitalWrite(markPin, HIGH);
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
        if ( markPin != 0 ) digitalWrite(markPin, LOW);
    }
