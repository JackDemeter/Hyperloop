# Hyperloop

### INTRO ###
Queen's University Hyperloop team 2019 software structure

This project uses 3 BMO055 IMU sensors in combination with 2 Infrared Proximity Sensor Long Range - Sharp (GP2Y0A02YK0F)
as well as 3 0-100 psi transducer with 0.5 to 4.5 Vdc output and  numerous Negative Temperature Coefficient (NTC) thermistor
placed around the pod to ensure that the pod is with safe parameters

Each IMU will be placed on its own board and read to a master board using I2C or SPI (still choosing).
Another board will manage all of the temperature and pressure sensors, approximately 30 sensors in total will be combined with analog MUX to iterate through each value after being passed to the as data to the communication arduino, this arduino will interact with the the ubiquiti rocket M900 to communicate with the central hub.


### COMMUNICATION PROTOCOL ###

Using data from https://dl.ubnt.com/datasheets/rocketm/RocketM_DS.pdf

The Ubiquiti Rocket M900 communicates at an interval of 900 MHz with a throughput of 150/Mbps, it has one 10/100Mbps Ethernet port.
Must be aware of the however noise levels are typically higher. Can pair with a Point to Point link or Point to Multi Point network.

64 MB SDRAM, 8 MB Flash

The main Arduino will talk to the M900 using the 10/100 ethernet port on the radio.
Can operate between 3MHz and 16MHz.

# Arduino Structure

### MAIN CONTROLLER ###

The main controller will be an Arduino Mega because it has more I/O pins (specifically analog) and has 4 serial ports to allow for communication to numerous internal boards. It operates at 16MHz.

The main arduino will be directly connected to the motorcontrollers using a 3 input AND gate that is also connected to a communication arduino to enable remote shut off. As well as a physical switch that will be mounted on the arduino, which will allow for the hyperloop pod to be turned on and off once placed on the track and prevent motor operation in case of an arduino malfunction. 

### NETWORK CONTROLLER ###

This controller will be used to communicate with the Ubiquiti M900 Rocket via the Arduino Ethernet Shield 2 this the board will be connected to the Main Controller board using the Serial port, this allows the remote commands to the pod. It will have a digital output to the motor controllers via the AND gate to allow for remote stopping.

 
Written by Jack Demeter
Uses libraries and code provided by adafruit for BMO055 sensor
