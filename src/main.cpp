#include <Arduino.h>
#include <Streaming.h>

#include "CommandCodes.h"
#include "SapienSignal.h"

// Demonstration code for shiftOut
int MARK = 13;
int SERDATA = 7;

SapienSignal Command(SERDATA, MARK);

void setup() {
   Serial.begin(115200);
   Command.begin();
}

// Test with shiftOut which triggers at ~80kHz  We need it to fire at 1.5 kHz
// Copy the internal version and slow it down.
void loop() {
    uint32_t cc;
    byte command;

   if (Serial.available()>0) {
        
        digitalWrite(MARK, HIGH);
        cc = Serial.read() & 0xFF;
        if (cc == 'S')      command = Demo_1;
        else if (cc == 'U') command = Demo_2;
        else if (cc == 'D') command = Dance;
        else command = 0x00;

        Serial << "Cmd ["<< _BYTE(cc) <<"] complete : 0x" << _HEX(command) << endl;

        Command.shiftOut(command);

    }
    cc = 0;
    delay(100);

}