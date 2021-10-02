#include <Arduino.h>

#define I2C_PERIPH_ADDRESS 0x14 // the 7-bit address (remember to change this when adapting this example)
#include <TinyWireS.h>
#include "SapienSignal.h"

// The default buffer size
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

// Demonstration code for shiftOut
int MARK = PB5;
int IRDATA = PB1;

SapienSignal Command(IRDATA, MARK);

// Declarations
void requestEvent();
void receiveEvent(uint8_t howMany);

// Incoming messages
volatile uint8_t i2c_regs[] = {'-', '-',};
// Commands are always 2 bytes, a character 
//  'C' command and a byte which is the IR command to send to RoboSapien
//  'F' command to flash the LED (mostly for debugging) or for decoration
//

// Tracks the current register pointer position
volatile byte reg_position = 0;
const byte reg_size = sizeof(i2c_regs);

// Signalling
void blink(uint8_t color, uint8_t blinks=2);
const uint8_t RED = 0x43;  // PB4<<8 + PB3;
const uint8_t GRN = 0x34;  // PB3<<8 + PB4;

/**
 * Setup the pins on power up
 **/
void setup() {
    // pins that control the BiColor LED for blink
    pinMode(3, OUTPUT); // OC1B-, Arduino pin 3, ADC
    pinMode(4, OUTPUT); // OC1B-, Arduino pin 4, ADC
    digitalWrite(3, LOW); // Start LOW
    digitalWrite(4, LOW); // Start LOW

    Command.begin(); // do this before setting up interrupts.

    /**
     * Reminder: taking care of pull-ups is the masters job
     */
    TinyWireS.begin(I2C_PERIPH_ADDRESS);
    TinyWireS.onReceive(receiveEvent);
    TinyWireS.onRequest(requestEvent);
    
    // blink the LED to indicate we are ready.
    blink(RED, 4);
    blink(GRN, 4);
}

// State monitors
const int IDLE = 0;             // nothing happening
const int SEND_COMMAND = 1;
const int FLASH_RED = 2;
const int FLASH_GRN = 3;
const int RESPOND = 4;

volatile int state = IDLE;

void loop() {
    /**
     * This is the only way we can detect stop condition (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=984716&sid=82e9dc7299a8243b86cf7969dd41b5b5#984716)
     * it needs to be called in a very tight loop in order not to miss any (REMINDER: Do *not* use delay() anywhere, use tws_delay() instead).
     * It will call the function registered via TinyWireS.onReceive(); if there is data in the buffer on stop.
     */
    TinyWireS_stop_check();

    if (state == SEND_COMMAND) {
        uint8_t times = i2c_regs[1] & 0x0F; // lower nibble
        Command.shiftOut(i2c_regs[1]);
        blink(GRN, times);
        state = IDLE;

    } else if (state == FLASH_RED) {
        uint8_t times = i2c_regs[1] & 0x0F; // lower nibble
        blink(RED, times);
        state = IDLE;

    } else if (state == FLASH_GRN) {
        uint8_t times = i2c_regs[1] & 0x0F; // lower nibble
        blink(GRN, times);
        state = IDLE;
    }

}


/**
 * blink controlling led to indicate state
 * bi-colored LED alliows 3 colors. 
 *  All pins are low moving into this routine.
 *  RED (flash pin 1) GREEN (flash pin 2)
 * This may be removed if it takes up too time for good I2C communication.
 * Note that we will run this after an IDLE state terminates so likelyhood
 * of loosing a signal will be small. We use special 'delay' routine
 **/
void blink(uint8_t color, uint8_t blinks) {

    while(blinks--) {
        digitalWrite(color & 0x0F, LOW);
        tws_delay(50);
        digitalWrite(color & 0x0F, HIGH);
        tws_delay(75);
    }
    digitalWrite(color & 0x0F, LOW);
    digitalWrite((color & 0xF0) >> 4, LOW);
}


/**
 * This is called for each read request we receive, never put more than one byte of data (with TinyWireS.send) 
 * to the send-buffer when using this callback
 */
void requestEvent() { 
    TinyWireS.send(i2c_regs[0]); // send last command gotten
    state = RESPOND;
}

/**
 * The I2C data received -handler
 *
 * This needs to complete before the next incoming transaction (start, data, restart/stop) on the bus does
 * so be quick, set flags for long running tasks to be called from the mainloop instead of running them directly,
 */
void receiveEvent(uint8_t howMany) {
    // In DEMO program, may or may not be necessary
    if (howMany < 1 || howMany > TWI_RX_BUFFER_SIZE) {
        // Sanity-check
        //  state = IDLE;
        return;
    }

    // successive reads don't work. need to do this asyncronously
    // if (howMany > 0) {
    //     i2c_regs[reg_position] = TinyWireS.receive(); 
    //     i2c_regs[1] = TinyWireS.receive();
    // }

    // async reads.  Grab from the buffer.
    // while(howMany--) {
    //     i2c_regs[reg_position] = TinyWireS.receive();
    //     reg_position++;
    //     if (reg_position >= reg_size) {
    //         reg_position = 0;
    //         if (i2c_regs[0] == 'C')
    //             state = SEND_COMMAND;
    //         if (i2c_regs[0] == 'F')
    //             state = FLASH_LED;        
    //         }
    //     }

    // Different example, more direct. Didn't work as advertised
    while (1 < TinyWireS.available()) { // loop through all but the last
        i2c_regs[0] = TinyWireS.receive();      // receive byte as a character
    }
    i2c_regs[1] = TinyWireS.receive();    // receive byte as an integer
    if (i2c_regs[0] == 'C')
        state = SEND_COMMAND;
    else if (i2c_regs[0] == 'R')
        state = FLASH_RED;
    else if (i2c_regs[0] == 'G')
        state = FLASH_GRN;
    // reg_position = TinyWireS.receive();
    // howMany--;
    // if (!howMany) {
    //     // This write was only to set the buffer for next read
    //     return;
    // }

    // Demo from documentation
    // while(howMany--) {
    //     i2c_regs[reg_position] = TinyWireS.receive();
    //     // if ( reg_position == 0 // If it was the first register
    //     //     && bitRead(i2c_regs[0], 7) // And the highest bit is set
    //     //     && !ADC_ConversionInProgress() // and we do not actually have a conversion running already
    //     //     )
    //     // {
    //     //     start_conversion = true;
    //     // }
    //     reg_position++;
    //     if (reg_position >= reg_size) {
    //         reg_position = 0;
    //         if (i2c_regs[0] == 'C')
    //             state = SEND_COMMAND;
    //         if (i2c_regs[0] == 'F')
    //             state = FLASH_LED;
    //     }
    // }
}
