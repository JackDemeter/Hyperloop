// Double BNO testing

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno1 = Adafruit_BNO055(55,0x28);
Adafruit_BNO055 bno2 = Adafruit_BNO055(55,0x29);

 
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno1.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO1 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  if(!bno2.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO2 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno1.setExtCrystalUse(true);
  bno2.setExtCrystalUse(true);
  delay(1000);
}
 
void loop(void) 
{
  /* Get a new sensor event */ 
  
  sensors_event_t event1; 
  bno1.getEvent(&event1);

  
  sensors_event_t event2; 
  bno2.getEvent(&event2);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event1.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event1.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event1.orientation.z, 4);
   Serial.print("\t\tX: ");
  Serial.print(event2.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event2.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event2.orientation.z, 4);
  Serial.println("");
  
  delay(100);
}
