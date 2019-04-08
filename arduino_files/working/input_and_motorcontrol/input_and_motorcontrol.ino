/* Hyperloop 2018 Main Arduino
 * 
 * This arduino is used to determine if the pod exceeds the safety threshhold
 * as well as to communicate with the raspberry pi to notify the base station 
 * about the state of the pod. 
 * 
 * The arduino reads sensor data including the pressure, IMUs and thermal sensors
 * (2 placed on batteries, individual motors(4), axels(2?), internal compartment, 
 * and chassis) using analong multiplexers
 * 
 * The arduino outputs a digital signal to the motorcontrollers through an AND gate 
 * that ensures that both the arduino and raspberry pi is indicating a launch state
 * 
 * The arduino communicates to the RP via UART reporting the state and individual
 * sensors to be sent over the network port
 * 
 * Created By Jack Demeter, 2019 
 */


//      Libraries       //

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>





void setup() {
  // put your setup code here, to run once:

  //      Variables       //
  pinMode(2, OUTPUT);   //pin setup for motorcontroller

  



  // TODO setup IMU
  // TODO setup pressure
  // TODO setup temp sensors
  // TODO setup UART conection
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // TODO read all sensor inputs
  // Determine if sensor inputs are within safe range
  // Report data through the UART port
  // Report safe or not through digital pin

}
