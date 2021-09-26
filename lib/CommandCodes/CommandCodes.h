/**
 * Define the single byte command codes for the RoboSapien robot.
 **/

#ifndef Command_Codes_h
#define Command_Codes_h

static char turn_right = 0x80;   // - turn right (on left side of remote)
static char right_arm_up = 0x81;   // - right arm up (upper left button on remote)
static char right_arm_out = 0x82;    // - right arm out
static char tilt_body_right = 0x83;    // - tilt body right
static char right_arm_down = 0x84;    // - right arm down
static char right_arm_in = 0x85;    // - right arm in
static char walk_forward = 0x86; // - walk forward
static char walk_backward = 0x87;// - walk backward
static char turn_left = 0x88;    // - turn left (on right side of remote)
static char left_arm_up = 0x89;     // - left arm up (upper right button on remote)
static char left_arm_out = 0x8A;     // - left arm out
static char tilt_body_left = 0x8B;    // - tilt body left
static char left_arm_down = 0x8C;     // - left arm down
static char left_arm_in = 0x8D;     // - left arm in
static char stop     = 0x8E;     // - stop

#endif