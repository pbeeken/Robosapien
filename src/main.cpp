#include <Arduino.h>
#include <Streaming.h>

// Demonstration code for shiftOut
int MARK = 13;
int SERCLK = 6;
int SERDATA = 7;

static uint32_t SHIFT_DELAY = 300;
void custom_shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST) {
			digitalWrite(dataPin, val & 1);
			val >>= 1;
		} else {	
			digitalWrite(dataPin, (val & 128) != 0);
			val <<= 1;
		}
			
		digitalWrite(clockPin, HIGH);
        delayMicroseconds(SHIFT_DELAY);
		digitalWrite(clockPin, LOW);
        delayMicroseconds(SHIFT_DELAY);	
	}
}


void setup() {
   Serial.begin(115200);

   pinMode(MARK, OUTPUT);
   pinMode(SERDATA, OUTPUT);
   pinMode(SERCLK, OUTPUT);

   digitalWrite(MARK, LOW);
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

    // for( byte i=0; i<255; i++) {
    //     digitalWrite(MARK, HIGH);
    //     //Serial << "On";
    //     custom_shiftOut(SERDATA, SERCLK, MSBFIRST, i);
    //     digitalWrite(MARK, LOW);
    //     //Serial << "Off";
    //     digitalWrite(SERDATA, LOW);   //  Stop scope output flicker.
    //     delay(10);
    // }

    if (Serial.available()>0) {
        
        digitalWrite(MARK, HIGH);
        cc = Serial.read() & 0xFF;
        if (cc == 'S')      command = stop;
        else if (cc == 'U') command = right_arm_up;
        else if (cc == 'D') command = right_arm_down;
        else command = 0x00;

        Serial << "Cmd ["<< _BYTE(cc) <<"] complete : 0x" << _HEX(command) << endl;

        custom_shiftOut(SERDATA, SERCLK, MSBFIRST, command);
        digitalWrite(SERDATA, LOW);   //  Stop scope output flicker.        
        digitalWrite(MARK, LOW);

    }
    cc = 0;
    delay(100);

}