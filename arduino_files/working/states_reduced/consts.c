#include <stdint.h>

// preset calculated values for when the pod should engage certain aspects
// must be flashed each time to change
// distances are in in meters and speeds are in m/s
const int BRAKE_DIST_THRESH = 800;
const int END_DIST_THRESH = 1000;
// speed that the pod coasts at (~10km/h)
const float COAST_SPEED_THRESH = 2.8;
// Variable value to set the maximum speed of the pod
// max speed that the pod attempts to achieve (~200km/h)
const float LAUNCH_SPEED_THRESH = 55.56;

// Packet data
const uint8_t TEAM_ID = 11;
