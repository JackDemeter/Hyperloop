#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <time.h>
#include <math.h>
#include <Wire.h>

// Initialize the states
//enum state;
//enum faultType;
//enum sensors;

void establishInternal(); // Creates a serial connection between state and network arduino
void establishExternal(); // Waits for network arduino to indicate network connection was made

void printState(state s); // Prints the current state that the pod is in
struct StateDetails;
