#include <Arduino.h>
#include "SapienSignal.h"

/**
 * Class that manages the serial output to the RoboSapien
 * to send the equivalent of the remote IR signal to the 
 * built in processor
 *  - Timing based on 1/1200 second clock (~.833ms)
 *  - Signal is normally high (idle, no IR).
 *  - Start: signal goes low for 8/1200 sec.
 *  - Data bits: for each of 8 data bits, space encoded signal depending on bit value
 *      - Sends the most significant data bit first
 *      - If the data bit is 0: signal goes high for 1/1200 sec, and low for 1/1200 sec.
 *      - If the data bit is 1: signal goes high for 4/1200 sec, and low for 1/1200 sec.
 *      - BTW: The first bit (msb) is always 1 (valid codes are from $80 to $FF)
 *  - When completed, signal goes high again.
 *  - No explicit stop bit. Minimal between signals is not known.
 **/
class SapienSignal {

private:
    uint8_t dataPin;
    uint8_t markPin;


public:
    /**
     * Establish the pins. dataPin and clockPin are required
     * markPin is for enveloping the signal for debugging. 
     * clockPin is equally redundant. We only use an async dataPin
     **/
    SapienSignal(uint8_t dataPin, uint8_t markPin=0) {
        this->dataPin = dataPin;
        this->markPin = markPin;
    }

    void begin() {
        pinMode(markPin, OUTPUT);
        pinMode(dataPin, OUTPUT);

        digitalWrite(markPin, LOW);
        digitalWrite(dataPin, HIGH);
    }

    void shiftOut(uint8_t val) {
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
};

