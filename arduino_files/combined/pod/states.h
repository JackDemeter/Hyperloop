#ifndef STATES_H
#define STATES_H

/******************************
 * INCLUDE SENSOR READING FILES
 ******************************/

 #include "lidar.c"
 #include "pressure_transducer.c"
 //etc, etc

 /* t1_val = transducer_vals(<ins pin num here>)
    t2_val = transducer_vals(<ins pin num here>)
    lidar_val = lidar_vals()
  */

enum state
{
  FAULT,
  STA,
  RTL,
  LAUNCH,
  COAST,
  BRAKE,
  CRAWL,
  STATES,
  STATE_NONE
};

enum faultType
{
  NONE,
  SETUP,
  COMM_NETWORK_LOSS,
  COMM_ARDUINO_LOSS,
  RTL_SKIP,
  FAULTS
};

state getState(Stream &refSer); // Gets the state as a character integer (ie '0') from a given serial port 
state checkState(state receivedState, state currentState, unsigned long *TSI,  int motor_pin, int brake_pin);
void dispState(int s);
void printState(state s);

#endif
