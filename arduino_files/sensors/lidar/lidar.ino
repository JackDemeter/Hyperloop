/*------------------------------------------------------------------------------

  LIDARLite Arduino Library
  v3/GetDistancePwm

  This example shows how to read distance from a LIDAR-Lite connected over the
  PWM interface.

  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite Ground (black) to Arduino GND
  LIDAR-Lite Mode control (yellow) to Arduino digital input (pin 3)
  LIDAR-Lite Mode control (yellow) to 1 kOhm resistor lead 1
  1 kOhm resistor lead 2 to Arduino digital output (pin 2)

  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

------------------------------------------------------------------------------*/

unsigned long pulseWidth;

void setup()
{
  Serial.begin(9600); // Start serial communications

  pinMode(8, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(8, LOW); // Set trigger LOW for continuous read

  pinMode(9, INPUT); // Set pin 3 as monitor pin
}

void loop()
{
  pulseWidth = pulseIn(9, HIGH); // Count how long the pulse is high in microseconds

  // If we get a reading that isn't zero, let's print it
  if(pulseWidth != 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
  }
}

float lidar_vals()
{
  pulseWidth = pulseIn(9, HIGH); // Count how long the pulse is high in microseconds
  return pulseWidth /= 10; // 10usec = 1 cm of distance
}
