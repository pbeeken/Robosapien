/**
 * Define the single byte command codes for the RoboSapien robot.
 **/

#ifndef Command_Codes_h
#define Command_Codes_h

const uint8_t walk_forward        = 0x86;   // - walk forward
const uint8_t walk_backward       = 0x87;   // - walk backward
const uint8_t right_turn_step	   = 0xA0;	// - right turn step
const uint8_t left_turn_step	   = 0xA8;	// - left turn step
const uint8_t forward_step	       = 0xA6;	// - forward step
const uint8_t backward_step	   = 0xA7;	// - backward step

const uint8_t turn_right          = 0x80;   // - turn right (on left side of remote)
const uint8_t turn_left           = 0x88;   // - turn left (on right side of remote)

const uint8_t tilt_body_right     = 0x83;   // - tilt body right
const uint8_t tilt_body_left      = 0x8B;   // - tilt body left

const uint8_t right_arm_up        = 0x81;   // - right arm up (upper left button on remote)
const uint8_t right_arm_out       = 0x82;   // - right arm out
const uint8_t right_arm_down      = 0x84;   // - right arm down
const uint8_t right_arm_in        = 0x85;   // - right arm in
const uint8_t left_arm_up         = 0x89;   // - left arm up (upper right button on remote)
const uint8_t left_arm_out        = 0x8A;   // - left arm out
const uint8_t left_arm_down       = 0x8C;   // - left arm down
const uint8_t left_arm_in         = 0x8D;   // - left arm in

const uint8_t right_hand_thump    = 0xA1;	// - right hand thump
const uint8_t right_hand_throw    = 0xA2;	// - right hand throw
const uint8_t left_hand_thump	  = 0xA9;	// - left hand thump
const uint8_t left_hand_throw	  = 0xAA;	// - left hand throw
const uint8_t right_hand_pickup   = 0xA4;	// - right hand pickup
const uint8_t left_hand_pickup    = 0xAC;	// - left hand pickup
const uint8_t lean_forward	      = 0xAD;	// - lean forward
const uint8_t lean_backward	      = 0xA5;	// - lean backward

const uint8_t right_hand_strike_3 = 0xC0;	// - right hand strike 3
const uint8_t right_hand_strike_2 = 0xC3;	// - right hand strike 2
const uint8_t right_hand_strike_1 = 0xC5;	// - right hand strike 1
const uint8_t left_hand_sweep	  = 0xC9;	// - left hand sweep
const uint8_t left_hand_strike_3  = 0xC8;	// - left hand strike 3
const uint8_t left_hand_strike_2  = 0xCB;	// - left hand strike 2
const uint8_t left_hand_strike_1  = 0xCD; // - left hand strike 1
const uint8_t right_hand_sweep	  = 0xC1;	// - right hand sweep

// Speech
const uint8_t high_5	          = 0xC4;	// - high 5
const uint8_t listen	          = 0xAB;	// - listen (ask, wait and ack.)
const uint8_t burp	              = 0xC2;	// - burp
const uint8_t oops            	  = 0xC7;	// - oops (fart)
const uint8_t talkback	          = 0xCC; // - talkback
const uint8_t roar	              = 0xCE;	// - roar
const uint8_t whistle	          = 0xCA;	// - whistle

// Demos
const uint8_t bulldozer	          = 0xC6;	// - bulldozer
const uint8_t All_Demo	          = 0xD0;	// - All Demo
const uint8_t Demo_1              = 0xD2;	// - Demo 1 (Karate skits)
const uint8_t Demo_2              = 0xD3;	// - Demo 2 (Rude skits)
const uint8_t Dance               = 0xD4;	// - Dance

// Power management
const uint8_t Power_Off           = 0xD1;	// - Power Off (drop snow-globe and say "Rosebud")
const uint8_t sleep	              = 0xA3;	// - sleep
const uint8_t reset	              = 0xAE;    // - reset
const uint8_t stop                = 0x8E;   // - stop

// These are probably not useful as we are abdicating progamatic control to the
// piggy back processor
const uint8_t Execute	          = 0xB0;	// - Execute (master command program execute)
const uint8_t Wakeup	          = 0xB1;	// - Wakeup
const uint8_t Right_Prog_Exec     = 0xB2;	// - Right (right sensor program execute)
const uint8_t Left_Prog_Exec	  = 0xB3;	// - Left (left sensor program execute)
const uint8_t Sonic_Prog_Exec	  = 0xB4;	// - Sonic (sonic sensor program execute)

#endif