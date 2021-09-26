#include <Arduino.h>
#include <Streaming.h>

// Demonstration code for shiftOut
int MARK = 13;
int SERCLK = 6;
int SERDATA = 7;

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
    uint8_t clockPin;
    uint8_t markPin;


public:
    /**
     * Establish the pins. dataPin and clickPin are required
     * markPin is for enveloping the signal for debugging. 
     **/
    SapienSignal(uint8_t dataPin, uint8_t clockPin, uint8_t markPin=0) {
        this->dataPin = dataPin;
        this->clockPin = clockPin;
        this->markPin = markPin;
    }

    void begin() {
        pinMode(markPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(dataPin, OUTPUT);

        digitalWrite(markPin, LOW);
        digitalWrite(dataPin, HIGH);
    }

    void shiftOut(uint8_t val) {
        const int BASIC_CLOCK = 833; // microseconds 
        const int CORR = 4;
        // flag the start of clocking
        if ( markPin != 0 ) digitalWrite(markPin, HIGH);
        // here we implement the sequence sending
        // START SEQUENCE
        digitalWrite(dataPin, LOW);
        delayMicroseconds(8*BASIC_CLOCK);
        digitalWrite(dataPin, HIGH);

        // loop over data
    	for (uint8_t i = 0; i < 8; i++)  {
            digitalWrite(clockPin,HIGH);
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
            digitalWrite(clockPin,LOW);
            }
        digitalWrite(dataPin, HIGH);

        // flag the end of clocking
        if ( markPin != 0 ) digitalWrite(markPin, LOW);
    }
};


// static uint32_t SHIFT_DELAY = 300;
// void custom_shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
// {
// 	uint8_t i;

// 	for (i = 0; i < 8; i++)  {
// 		if (bitOrder == LSBFIRST) {
// 			digitalWrite(dataPin, val & 1);
// 			val >>= 1;
// 		} else {	
// 			digitalWrite(dataPin, (val & 128) != 0);
// 			val <<= 1;
// 		}		
// 		digitalWrite(clockPin, HIGH);
//         delayMicroseconds(SHIFT_DELAY);
// 		digitalWrite(clockPin, LOW);
//         delayMicroseconds(SHIFT_DELAY);	
// 	}
// }

SapienSignal Command(SERDATA, SERCLK, MARK);


void setup() {
   Serial.begin(115200);
   Command.begin();
}

static byte turn_right = 0x80;   // - turn right (on left side of remote)
static byte right_arm_up = 0x81;   // - right arm up (upper left button on remote)
static byte right_arm_out = 0x82;    // - right arm out
static byte tilt_body_right = 0x83;    // - tilt body right
static byte right_arm_down = 0x84;    // - right arm down
static byte right_arm_in = 0x85;    // - right arm in
static byte walk_forward = 0x86; // - walk forward
static byte walk_backward = 0x87;// - walk backward
static byte turn_left = 0x88;    // - turn left (on right side of remote)
static byte left_arm_up = 0x89;     // - left arm up (upper right button on remote)
static byte left_arm_out = 0x8A;     // - left arm out
static byte tilt_body_left = 0x8B;    // - tilt body left
static byte left_arm_down = 0x8C;     // - left arm down
static byte left_arm_in = 0x8D;     // - left arm in
static byte stop     = 0x8E;     // - stop

// Test with shiftOut which triggers at ~80kHz  We need it to fire at 1.5 kHz
// Copy the internal version and slow it down.
void loop() {
    uint32_t cc;
    byte command;

   if (Serial.available()>0) {
        
        digitalWrite(MARK, HIGH);
        cc = Serial.read() & 0xFF;
        if (cc == 'S')      command = stop;
        else if (cc == 'U') command = right_arm_up;
        else if (cc == 'D') command = right_arm_down;
        else command = 0x00;

        Serial << "Cmd ["<< _BYTE(cc) <<"] complete : 0x" << _HEX(command) << endl;

        Command.shiftOut(command);

    }
    cc = 0;
    delay(100);

}