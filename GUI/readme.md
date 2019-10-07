## Hyperloop GUI ##

### Directory ###
Queen's University Hyperloop team 2019 software structure

#### Playground ####
contains the main GUI, to be run on the laptop
#### Requirements.txt ####
contains all of the libraries used for this project, once you have created a virtual environment, download this packages with:
*pip install -h "requirements.txt"*
#### UDP sending ####
Test code to send the UDP data, works with UDPrecieving and the Arduino network file
#### UDP recieving ####
Test code, displays content recieved for debugging purposes


### Sensor Monitoring ###

The arduino will monitor these sensors, as such it is important to include them in the GUI. Read SpaceX competition rules for more information about the required telemetry to be returned.

3 IMUs (Adafruit BMO055)
2 Laser sensor of choice with Class 1 Laser rating 
1 0-100 psi transducer (Adafruit MPRLS)
17 Negative Temperature Coefficient (NTC) thermistor 
	- one per battery(2), 
	- one per motor temperature sensors(4)
	- each axel temp(2)
	- internal compartment(1)
	- chassis(4)
	- brake calipers(4) 

to ensure that the pod is within safe operating parameters.

### COMMUNICATION PROTOCOL ###

Using data from https://dl.ubnt.com/datasheets/rocketm/RocketM_DS.pdf

The Ubiquiti Rocket M900 communicates at an interval of 900 MHz with a throughput of 150/Mbps, it has one 10/100Mbps 
Ethernet port. Must be aware of the however noise levels are typically higher. Can pair with a Point to Point link or 
Point to Multi Point network.

64 MB SDRAM, 8 MB Flash

The main Arduino will talk to the M900 using the 10/100 ethernet port on the radio.
Can operate between 3MHz and 16MHz.



#### Written by Jack Demeter ####
#### Uses libraries and code provided by adafruit for BMO055 and MPLRS sensors ####
