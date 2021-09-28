/**
 * Define the single byte command codes for the RoboSapien robot.
 **/

#ifndef Command_Codes_h
#define Command_Codes_h

const char walk_forward        = 0x86;   // - walk forward
const char walk_backward       = 0x87;   // - walk backward
const char right_turn_step	   = 0xA0;	// - right turn step
const char left_turn_step	   = 0xA8;	// - left turn step
const char forward_step	       = 0xA6;	// - forward step
const char backward_step	   = 0xA7;	// - backward step

const char turn_right          = 0x80;   // - turn right (on left side of remote)
const char turn_left           = 0x88;   // - turn left (on right side of remote)

const char tilt_body_right     = 0x83;   // - tilt body right
const char tilt_body_left      = 0x8B;   // - tilt body left

const char right_arm_up        = 0x81;   // - right arm up (upper left button on remote)
const char right_arm_out       = 0x82;   // - right arm out
const char right_arm_down      = 0x84;   // - right arm down
const char right_arm_in        = 0x85;   // - right arm in
const char left_arm_up         = 0x89;   // - left arm up (upper right button on remote)
const char left_arm_out        = 0x8A;   // - left arm out
const char left_arm_down       = 0x8C;   // - left arm down
const char left_arm_in         = 0x8D;   // - left arm in

const char right_hand_thump    = 0xA1;	// - right hand thump
const char right_hand_throw    = 0xA2;	// - right hand throw
const char left_hand_thump	   = 0xA9;	// - left hand thump
const char left_hand_throw	   = 0xAA;	// - left hand throw
const char right_hand_pickup   = 0xA4;	// - right hand pickup
const char left_hand_pickup    = 0xAC;	// - left hand pickup
const char lean_forward	       = 0xAD;	// - lean forward
const char lean_backward	   = 0xA5;	// - lean backward

const char right_hand_strike_3 = 0xC0;	// - right hand strike 3
const char right_hand_strike_2 = 0xC3;	// - right hand strike 2
const char right_hand_strike_1 = 0xC5;	// - right hand strike 1
const char left_hand_sweep	   = 0xC9;	// - left hand sweep
const char left_hand_strike_3  = 0xC8;	// - left hand strike 3
const char left_hand_strike_2  = 0xCB;	// - left hand strike 2
const char left_hand_strike_1  = 0xCD; // - left hand strike 1
const char right_hand_sweep	   = 0xC1;	// - right hand sweep

// Speech
const char high_5	           = 0xC4;	// - high 5
const char listen	           = 0xAB;	// - listen (ask, wait and ack.)
const char burp	               = 0xC2;	// - burp
const char oops            	   = 0xC7;	// - oops (fart)
const char talkback	           = 0xCC; // - talkback
const char roar	               = 0xCE;	// - roar
const char whistle	           = 0xCA;	// - whistle

// Demos
const char bulldozer	       = 0xC6;	// - bulldozer
const char All_Demo	           = 0xD0;	// - All Demo
const char Demo_1              = 0xD2;	// - Demo 1 (Karate skits)
const char Demo_2              = 0xD3;	// - Demo 2 (Rude skits)
const char Dance               = 0xD4;	// - Dance

// Power management
const char Power_Off           = 0xD1;	// - Power Off (drop snow-globe and say "Rosebud")
const char sleep	           = 0xA3;	// - sleep
const char reset	           = 0xAE;    // - reset
const char stop                = 0x8E;   // - stop

// These are probably not useful as we are abdicating progamatic control to the
// piggy back processor
const char Execute	            = 0xB0;	// - Execute (master command program execute)
const char Wakeup	            = 0xB1;	// - Wakeup
const char Right_Prog_Exec      = 0xB2;	// - Right (right sensor program execute)
const char Left_Prog_Exec	    = 0xB3;	// - Left (left sensor program execute)
const char Sonic_Prog_Exec	    = 0xB4;	// - Sonic (sonic sensor program execute)

#endif