/**
 * Define the single byte command codes for the RoboSapien robot.
 **/

#ifndef Command_Codes_h
#define Command_Codes_h

static char turn_right       = 0x80;   // - turn right (on left side of remote)
static char right_arm_up     = 0x81;   // - right arm up (upper left button on remote)
static char right_arm_out    = 0x82;   // - right arm out
static char tilt_body_right  = 0x83;   // - tilt body right
static char right_arm_down   = 0x84;   // - right arm down
static char right_arm_in     = 0x85;   // - right arm in
static char walk_forward     = 0x86;   // - walk forward
static char walk_backward    = 0x87;   // - walk backward
static char turn_left        = 0x88;   // - turn left (on right side of remote)
static char left_arm_up      = 0x89;   // - left arm up (upper right button on remote)
static char left_arm_out     = 0x8A;   // - left arm out
static char tilt_body_left   = 0x8B;   // - tilt body left
static char left_arm_down    = 0x8C;   // - left arm down
static char left_arm_in      = 0x8D;   // - left arm in
static char stop             = 0x8E;   // - stop

static char right_turn_step	 = 0xA0;	// - right turn step
static char right_hand_thump = 0xA1;	// - right hand thump
static char right_hand_throw = 0xA2;	// - right hand throw
static char sleep	         = 0xA3;	// - sleep
static char right_hand_pickup = 0xA4;	// - right hand pickup
static char lean_backward	 = 0xA5;	// - lean backward
static char forward_step	 = 0xA6;	// - forward step
static char backward_step	 = 0xA7;	// - backward step
static char left_turn_step	 = 0xA8;	// - left turn step
static char left_hand_thump	 = 0xA9;	// - left hand thump
static char left_hand_throw	 = 0xAA;	// - left hand throw
static char listen	         = 0xAB;	// - listen
static char left_hand_pickup = 0xAC;	// - left hand pickup
static char lean_forward	 = 0xAD;	// - lean forward
static char reset	         = 0xAE;    // - reset

static char right_hand_strike_3	= 0xC0;	// - right hand strike 3
static char right_hand_sweep	= 0xC1;	// - right hand sweep
static char burp	            = 0xC2;	// - burp
static char right_hand_strike_2	= 0xC3;	// - right hand strike 2
static char high_5	            = 0xC4;	// - high 5
static char right_hand_strike_1	= 0xC5;	// - right hand strike 1
static char bulldozer	        = 0xC6;	// - bulldozer
static char oops            	= 0xC7;	// - oops (fart)
static char left_hand_strike_3	= 0xC8;	// - left hand strike 3
static char left_hand_sweep	    = 0xC9;	// - left hand sweep
static char whistle	            = 0xCA;	// - whistle
static char left_hand_strike_2	= 0xCB;	// - left hand strike 2
static char talkback	        = 0xCC; // - talkback
static char left_hand_strike_1	= 0xCD; // - left hand strike 1
static char roar	            = 0xCE;	// - roar
static char All_Demo	        = 0xD0;	// - All Demo
static char Power_Off           = 0xD1;	// - Power Off (drop snow-globe and say "Rosebud")
static char Demo_1              = 0xD2;	// - Demo 1 (Karate skits)
static char Demo_2              = 0xD3;	// - Demo 2 (Rude skits)
static char Dance           	= 0xD4;	// - Dance

// These are probably not useful as we are abdicating progamatic control to the
// piggy back processor
static char Execute	            = 0xB0;	// - Execute (master command program execute)
static char Wakeup	            = 0xB1;	// - Wakeup
static char Right_Prog_Exec     = 0xB2;	// - Right (right sensor program execute)
static char Left_Prog_Exec	    = 0xB3;	// - Left (left sensor program execute)
static char Sonic_Prog_Exec	    = 0xB4;	// - Sonic (sonic sensor program execute)


#endif