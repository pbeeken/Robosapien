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
        switch(cc) {
            case '1': command = Demo_1;     break;
            case '2': command = Demo_2;     break;
            case 'D': command = Dance;      break;
            case 'B': command = bulldozer;  break;
            case 'W': command = Wakeup;     break;
            case 'Z': command = Power_Off;  break;
            case 'S': command = sleep;      break;

            case '4': command = high_5;     break;
            case '5': command = listen;     break;
            case '6': command = burp;       break;
            case '7': command = oops;       break;
            case '8': command = talkback;   break;
            case '9': command = whistle;    break;
            default:  command = 0x00;
        }
        Serial << "Cmd ["<< _BYTE(cc) <<"] complete : 0x" << _HEX(command) << endl;

        Command.shiftOut(command);

    }
    cc = 0;
    delay(100);

}