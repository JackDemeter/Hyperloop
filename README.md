# Hyperloop

## INTRO ##
Queen's University Hyperloop team 2019 software structure



## HARDWARE ##
A list of all hardware components used on this project:

TBD

# Arduino Structure #

## STATE ARDUINO ##

### Objective ###

The main controller will be an Arduino Due because it has more I/O pins (specifically analog) and has 4 serial ports to 
allow for communication to numerous internal boards. It operates at 16MHz.

The main arduino will be directly connected to the motorcontrollers using a 3 input AND gate that is also connected to a 
communication arduino to enable remote shut off. As well as a physical switch that will be mounted on the arduino, which 
will allow for the hyperloop pod to be turned on and off once placed on the track and prevent motor operation in case of 
an arduino malfunction. 

### Intro to Structure ###

The state Arduino Due will manage all temperature sensors, pressure sensors and IMU data via analong multiplexers. Based 
on the data provided by the sensors the board will determine if the pod is safe to operate. If so it will provide a 1 to 
an analog switch, allowing the networking arduino to communicate with the motorcontrollers. The State Arduino also
communicates with the networking arduino via I2C communication to report the state of the pod to the Networking Arduino.

### Sensor Monitoring ###

The arduino will monitor these sensors

3 IMUs (Adafruit BMO055)
2 Laser sensor of choice with Class 1 Laser rating (potentially Infrared Proximity Sensor Long Range (Sharp GP2Y0A02YK0F)) 
1 0-100 psi transducer (Adafruit MPRLS)
17 Negative Temperature Coefficient (NTC) thermistor 
	- one per battery(2), 
	- one per motor temperature sensors(4)
	- each axel temp(2)
	- internal compartment(1)
	- chassis(4)
	- brake calipers(4) 

and ensure that the pod is within safe operating parameters.

### Pin Layout ###


## NETWORK ARDUINO ##

This controller will be used to communicate with the Ubiquiti M900 Rocket via the Arduino Ethernet Shield 2 this the board 
will be connected to the Main Controller board using the Serial port, this allows the remote commands to the pod. It will 
have a digital output to the motor controllers via the AND gate to allow for remote stopping.


## FLASH ARDUINO ##

"In order for SpaceX to determine Pod speeds while in the Hyperloop tube, Pods are required to come equipped with hardware 
that allows for proper detection. The method of speed detection involves using on-Pod reflective laser sensors that detect 
the retro-reflective tape strips in the tube. An average speed between tape strips is than calculated and broadcast over 
the network using an on-Pod processor. 
Teams should have the following equipment on their Pods to accomplish this: 
1. 1x Arduino Uno 
2. 1x SainSmart Ethernet shield  
3. 2x Laser sensor of choice with Class 1 Laser rating (safe for viewing with naked eye) 

The laser sensors should be wired in such a way that they interface to the Arduino as such: 
1. Left side laser sensor on pin 2 of the Arduino, rising edge trigger with a 3.3V to 5V level when under reflective tape. 
2. Right side laser sensor on pin 3 of the Arduino, rising edge trigger with a 3.3V to 5V level when under reflective tape.

The Arduino shall be on the same wireless network as the Pod to allow communication in the tube via the Ubiquiti Rocket M900 radios. 
SpaceX developed code for the Arduino will be flashed to Pods during Competition Week. "

Quoted from 2019 SpaceX Hyperloop Pod Competition Rules and Requirements (November 30, 2018)
 


# COMMUNICATION PROTOCOL #

Using data from https://dl.ubnt.com/datasheets/rocketm/RocketM_DS.pdf

The Ubiquiti Rocket M900 communicates at an interval of 900 MHz with a throughput of 150/Mbps, it has one 10/100Mbps 
Ethernet port. Must be aware of the however noise levels are typically higher. Can pair with a Point to Point link or 
Point to Multi Point network.

64 MB SDRAM, 8 MB Flash

The main Arduino will talk to the M900 using the 10/100 ethernet port on the radio.
Can operate between 3MHz and 16MHz.



##### Written by Jack Demeter #####
##### Uses libraries and code provided by adafruit for BMO055 and MPLRS sensors #####
