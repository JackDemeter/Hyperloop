/*
Hyperloop Networking Arduino code 2018

This is the main script to run on the networking arduino of the hyperloop pod

1. This Arduino  is connected to 2 other arduinos through UART or Serial port
    - Arduino 1 passes the 'state' of the pod, essentially letting the pod know if it is operational based on
      the temperature, pressure, and IMU data is within the safe operational limits required
    - Arduino 2 passes the speed of the pod based on the calculations provided by spaceX, aka 'the flash arduino'
2. The RP is linked to the Ubiquiti M900 Rocket radio via ethernet cable (10/100Mbps Ethernet port) and sends packets
required by the spaceX team, read the 2019 competition details for more information (probably faster than reading this
code) this program will likely include the 'mock-receiver.py' python file provided by SpaceX
3. "This is gonna be fun" -Jack before writing the code

Created by Jack Demeter 2018
*/

//     LIBRARIES       //

// Libraries for ethernet shield 
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

// master slave library
#include <Wire.h> 


//     VARIABLES       //

pinMode(2, OUTPUT); // PLACE LEDs ON PIN 2 (RGB STRIP??)



enum state 
{
  FAULT,
  SAFE,
  RTL,  //Ready To Launch
  LAUNCH,
  COAST,
  BRAKE,
  CRAWL,
  NUM_STATE
};

enum crit_state 
{
  CRIT_FAULT,
  CRIT_SAFE,
  CRIT_ACTION
};





//     FUNCTIONS       //

/*
 * STATE DATA:
 * 
 * 0: Fault – When the Pod is in any fault state. 
 * 1: Safe to Approach – Any state where the Pod is on, not moving and safe for team members and SpaceX volunteers to approach. The Pod should go back to transmitting this state at the end of the run. 
 * 2: Ready to Launch – Any state where the Pod is ready to launch but not accelerating. 
 * 3: Launching – Any state where the Pod is commanding propulsion with the goal of achieving the highest velocity for the run. 
 * 4: Coasting – Any state where the Pod is moving but not accelerating or decelerating. 
 * 5: Braking – Any state where the Pod is decelerating using its braking mechanism, a Pod can stay in this state after having come to a full stop but should eventually go to Safe to approach. 
 * 6: Crawling – Any state where the Pod is commanding propulsion with the goal of moving the Pod while not achieving the highest velocity for the run.
 * 
 */

// TODO create state functions

void fault(init_state)
{
  // mark the state the pod was in when the error started
  state current_state = init_state;
  while (current_state == state):
  {
    // TODO report data
    
    // TODO convert ethernet signal such that any change in the current signal causes the pod to shut off.
    current_state = get_state();
  }
  exit();
  // Doesn't allow access to any other states
}


void safe()
{
  state current_state = get_state();
  if (state == RTL):
  {
    digitalWrite()
  }
  // Nothing happens in this state however it allows for the state to be changed to RTL after time period
  // TODO report data
  
  // TODO convert ethernet signal such that any change in the current signal causes the pod to shut off.
  
  // Doesn't allow access to any other states
}

// TODO, throw error if any issue comes up, catch function

// TODO get_state() get ethernet state data from the base

// TODO create event log (stretch goal)


/* 
 *  setup requirements:   
 *  - a port for communicating between the state arduino and the networking arduino, where networking arduino is slave in an I2C communication    
 *  - an analog input to the motor controller (save 3 incase needed)     
 *  - set up 2 'ethernet shield 2's, 1 for radio output, one for flash input
 *  - missing anything? brb
 */

void setup():
{
  
}
    

/*
 * loop requirements:    
 * - Determine the state to output based on the data recieved from the state arduino and network input     
 * - give analog value based on a given value     
 * - safety button to allow the pod to go into a launch state
 * 
 */

void loop():
    // allows for over ethernet communication to the pod
    crit_state = read_state()
    state = det_state(crit_state, command)
    if state == 0:
        // remote deactivation of the pod, also occurs if no data is heard/ether is lost
        active = False

    else if state == 1:
        // safe to approach: motors cannot be engaged
        break
        // TODO listen for a case when the next state is stepped into
    else if state == 2:
        // ready to launch: can only reach this state from state 2
        break
    else if state == 3:
        // launch: ZOOM
        break
    else if state == 4:
        // coast
        break
    else if state == 5:
        // brake until a stop is reached
        breaks



// Engage listen mode
while (True):
    // switches the pod to no longer be able to receive commands however still logs and reports data over ethernet until
    // pod manually shut off
    // TODO consider implementing a remote shutoff
    conv_to_packet()


