"""
Hyperloop Raspberry Pi(RP) code 2018

This is the main script to run on the raspberry pi of the hyperloop pod

1. This RP is connected to 2 arduinos through UART
    - Arduino 1 passes the 'health state' of the pod, essentially letting the pod know if it is operational based on
      the temperature, pressure, and IMU data is within the safe operational limits required
    - Arduino 2 passes the speed of the pod based on the calculations provided by spaceX, aka 'the flash arduino'
2. The RP is linked to the Ubiquiti M900 Rocket radio via ethernet cable (10/100Mbps Ethernet port) and sends packets
required by the spaceX team, read the 2019 competition details for more information (probably faster than reading this
code) this program will likely include the 'mock-receiver.py' python file provided by SpaceX
3. "This is gonna be fun" -Jack before writing the code

Created by Jack Demeter 2018
"""

###     LIBRARIES       ###

# determine a library to create packet data
# det library to read ethernet data
# library for UART?

###     FUNCTIONS       ###


def conv_to_packet():
    # creates a string? that is set up and sent as a packet
    packet = [] # 34 bytes
    return packet

def det_state(crit_state, command):
    # based on the critical state provided by the arduino and the radio command determine the pod state
    state = crit_state + command
    # TODO add radio command
    return state

def read_command():
    # read from the radio to determine the command
    return command

def read_state():
    # looks at UART input to determine current state of the pod
    return state



###     VARIABLES       ###


active = True # based on hardware switch being on and having an ethernet connection

# TODO, throw error if any issue comes up


# TODO create event log
# TODO create typedef for state (or a chart)


###     MAIN            ###

while (active):
    # allows for over ethernet communication to the pod
    command = read_command()
    crit_state = read_state()
    state = det_state(crit_state, command)
    if state == 0:
        # remote deactivation of the pod, also occurs if no data is heard/ether is lost
        active = False

    elif state == 1:
        # safe to approach: motors cannot be engaged
        break
        # TODO listen for a case when the next state is stepped into
    elif state == 2:
        # ready to launch: can only reach this state from state 2
        break
    elif state == 3:
        # launch: ZOOM
        break
    elif state == 4:
        # coast
        break
    elif state == 3:
        # launch: ZOOM
        breaks



# Engage listen mode
while (True):
    # switches the pod to no longer be able to receive commands however still logs and reports data over ethernet until
    # pod manually shut off
    # TODO consider implementing a remote shutoff
    conv_to_packet()

