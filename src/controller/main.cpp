#include <Arduino.h>
#include <Streaming.h>
#include <Wire.h>
#include "CommandCodes.h"
#include "SapienSignal.h"  Now in the I2C Peripheral

#define I2C_PERIPH_ADDRESS 0x14 // the 7-bit address (remember to change this when adapting this example)
// Demonstration code for shiftOut
 int MARK = LED_BUILTIN;
 int SERDATA = DD7;

SapienSignal Command(SERDATA, MARK);

void setup() {
    Serial.begin(115200);
    Wire.begin(I2C_PERIPH_ADDRESS);

    Command.begin();
}

// This is the basic test bench for the control of the RoboSapien.
// Test with shiftOut which triggers at ~80kHz  We need it to fire at 1.5 kHz
// Copy the internal version and slow it down.
void loop() {

    byte command[2];

    if (Serial.available()>1) {
        command[0] = Serial.read() & 0xFF;
        command[1] = Serial.read() & 0xFF; // english language code
        if (command[0]=='C') {
            //command[0] = 'C';
            switch(command[1]) {
                case '1': command[1] = Demo_1;     break;
                case '2': command[1] = Demo_2;     break;
                case 'D': command[1] = Dance;      break;
                case 'B': command[1] = bulldozer;  break;
                case 'W': command[1] = Wakeup;     break;
                case 'Z': command[1] = Power_Off;  break;
                case 'S': command[1] = sleep;      break;

                case '4': command[1] = high_5;     break;
                case '5': command[1] = listen;     break;
                case '6': command[1] = burp;       break;
                case '7': command[1] = oops;       break;
                case '8': command[1] = talkback;   break;
                case '9': command[1] = whistle;    break;
                case '0': command[1] = stop;       break;
                default:  command[1] = 0x00;
                }
            Serial << "Cmd ["<< _BYTE(command[0]) <<"] complete : 0x" << _HEX(command[1]) << endl;
            Wire.beginTransmission(I2C_PERIPH_ADDRESS);
            Wire.write(command, 2);
            Wire.endTransmission(true);
            Command.shiftOut(command[1]);
            Wire.requestFrom(I2C_PERIPH_ADDRESS, 1);  // request a single byte from peripheral device
            while(Wire.available()) {  // slave may send less than requested
                char c = Wire.read();  // receive a byte as character
                Serial << "  Rcd ["<< _BYTE(c) <<"]" << endl;
                }

        } else if (command[0]=='R' || command[0]=='G') {
            //command[0] = 'F';
            command[1] = command[1] & 0x0F;  // just take the lowest 4 bits of the ascii character
            Serial << "Cmd ["<< _BYTE(command[0]) <<"] complete : #" << _DEC(command[1]) << endl;
            Wire.beginTransmission(I2C_PERIPH_ADDRESS);
            Wire.write(command, 2);
            Wire.endTransmission();

            Wire.requestFrom(I2C_PERIPH_ADDRESS, 1);  // request a single byte from peripheral device
            while(Wire.available()) {  // slave may send less than requested
                char c = Wire.read();  // receive a byte as character
                Serial << "  Rcd ["<< _BYTE(c) <<"]" << endl;
                }
        }

    }
    command[0] = 0;
    delay(100);
}