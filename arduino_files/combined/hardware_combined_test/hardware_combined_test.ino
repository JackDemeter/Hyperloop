/* 
This is a test script for merging the individual sensor code.
Added so far:
 - IMU
 - Lidar
 - Laser sensor
 - Pressure transducer
 - Temperature (multiplexer)
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno1 = Adafruit_BNO055(55,0x28);
Adafruit_BNO055 bno2 = Adafruit_BNO055(55,0x29);

// adjust these values to calibrate pressure transducer
const float PT_SLOPE = 0.126;
const float PT_BIAS = -0.5 * 1024 / 5 - 5.0/PT_SLOPE; //extra 5.0 added in experimentally 26/10

// Pin Assignments
int transducer = A0;
int reset_IMU = 2;
int lidar_trigger = 8;
int lidar_monitor = 9;
int laser = 22;
int MP_bit1 = 22;
int MP_bit2 = 23;
int MP_bit4 = 24;
int temp = A0;

float pressure;

void setup() {
  Serial.begin(9600); // set up a serial monitor for writing analog values
  
  // Pin setups
  pinMode(transducer, INPUT);
  pinMode(reset_IMU, OUTPUT);
  pinMode(lidar_trigger, OUTPUT);
  pinMode(lidar_monitor, INPUT);
  pinMode(laser, INPUT);
  pinMode(MP_bit1, OUTPUT);
  pinMode(MP_bit2, OUTPUT);
  pinMode(MP_bit4, OUTPUT);
  pinMode(temp, INPUT);
  
  // IMU
  digitalWrite(reset_IMU,HIGH);
  delay(500);
  digitalWrite(reset_IMU,LOW);
  delay(1000);
  digitalWrite(reset_IMU,HIGH);

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

  // Lidar
  digitalWrite(lidar_trigger, LOW); // Set trigger LOW for continuous read

  // Laser sensor
  Serial.begin(9600);
}

void loop()
{
  // Pressure transducer
  pressure = PT_SLOPE * ((float)analogRead(transducer) + PT_BIAS);  
  Serial.print("Pressure");
  Serial.print(":\t");
  Serial.print(pressure);
  Serial.print("psi");
  Serial.println();

  // IMU
  sensors_event_t event1; 
  bno1.getEvent(&event1);

  sensors_event_t event2; 
  bno2.getEvent(&event2);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event1.x, 4);
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

  pulseWidth = pulseIn(lidar_monitor, HIGH); // Count how long the pulse is high in microseconds

  // If we get a reading that isn't zero, let's print it
  if(pulseWidth != 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
    Serial.println(pulseWidth); // Print the distance
  }
  
  // Laser sensor
  Laser_reading = digitalRead(laser)
  Serial.print(Laser_reading);

  // Temperature
  for (int x = 0; x < 2; x++)
  {
    digitalWrite(MP_bit4, x);
    for (int y = 0; y < 2; y++)
    {
      digitalWrite(MP_bit2, y);
      for (int z = 0; z < 2; z++)
      {
        digitalWrite(MP_bit1, z);
        Serial.print((float(analogRead(temp))*3.3/1024-0.5)*1000/19.5);
        Serial.print('\t');
        
      }
    }
  }
  Serial.println();
}
