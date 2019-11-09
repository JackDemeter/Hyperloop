/*  Sensor testing code
    Queen's Hyperloop Design team
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//global vars
// adjust these values for calibration
const float PRESSURE_SLOPE = 0.126;
const float BIAS = -0.5 * 1024 / 5;

// PIN LAYOUT
int reset_IMU = 2;
int lidar_trigger = 8;
int lidar_monitor = 9;
// multiplexer addresses
int bit1 = 22;
int bit2 = 23;
int bit4 = 24;

int laser_left = 28;
int laser_right = 29;

int temp = A0;
int transducer = A7;

unsigned long startTime = 0;

// IMU initializing
Adafruit_BNO055 bno1 = Adafruit_BNO055(55, 0x28);
Adafruit_BNO055 bno2 = Adafruit_BNO055(55, 0x29);

// pressure transducer data
float pressure;

unsigned long pulseWidth;

void setup(void)
{
  // reset the IMUs to the proper addresses to ensure proper connection
  pinMode(reset_IMU, OUTPUT);
  digitalWrite(reset_IMU, HIGH);
  delay(500);
  digitalWrite(reset_IMU, LOW);
  delay(1000);
  digitalWrite(reset_IMU, HIGH);

  pinMode(lidar_trigger, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(lidar_trigger, LOW); // Set trigger LOW for continuous read

  pinMode(lidar_monitor, INPUT); // Set pin 3 as monitor pin

  pinMode(laser_left, INPUT);
  pinMode(laser_right, INPUT);

  pinMode(transducer, INPUT);

  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit4, OUTPUT);
  pinMode(temp, INPUT);

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if (!bno1.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO1 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  if (!bno2.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO2 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  bno1.setExtCrystalUse(true);
  bno2.setExtCrystalUse(true);
  delay(1000);
}

void loop(void)
{
  Serial.print(millis()-startTime);
  startTime = millis();


  // IMU

  sensors_event_t event1;
  bno1.getEvent(&event1);


  sensors_event_t event2;
  bno2.getEvent(&event2);

  /* Display the floating point data */
  /*
    Serial.print("oX: ");
    Serial.print(event1.orientation.x, 4);
    Serial.print("\toY: ");
    Serial.print(event1.orientation.y, 4);
    Serial.print("\toZ: ");
    Serial.print(event1.orientation.z, 4);
    Serial.print("\t\toX: ");
    Serial.print(event2.orientation.x, 4);
    Serial.print("\toY: ");
    Serial.print(event2.orientation.y, 4);
    Serial.print("\toZ: ");
    Serial.print(event2.orientation.z, 4);
    Serial.println("");
  */

  event1.orientation.x;
  event1.orientation.y;
  event1.orientation.z;

  event2.orientation.x;
  event2.orientation.y;
  event2.orientation.z;


  imu::Vector<3> ACCEL1 = bno1.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> ACCEL2 = bno1.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  /*
    Serial.print("aX: ");
    Serial.print(ACCEL1.x(), 4);
    Serial.print("\taY: ");
    Serial.print(ACCEL1.y(), 4);
    Serial.print("\tZa: ");
    Serial.print(ACCEL1.z(), 4);
    Serial.print("\t\taX: ");
    Serial.print(ACCEL2.x(), 4);
    Serial.print("\taY: ");
    Serial.print(ACCEL2.y(), 4);
    Serial.print("\taZ: ");
    Serial.print(ACCEL2.z(), 4);
  */
  ACCEL1.x();
  ACCEL1.y();
  ACCEL1.z();
  ACCEL2.x();
  ACCEL2.y();
  ACCEL2.z();

  // LIDAR
  Serial.print("\tIMU"); Serial.print(millis()-startTime);
  
  pulseWidth = pulseIn(lidar_monitor, HIGH); // Count how long the pulse is high in microseconds

  // If we get a reading that isn't zero, let's print it
  if (pulseWidth != 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
    //Serial.print("\tlidar: ");
    //Serial.print(pulseWidth); // Print the distance
  }
  
  digitalRead(laser_left);
  digitalRead(laser_right);
  /*
    Serial.print("\tLaser left: ");
    Serial.print(digitalRead(laser_left));
    Serial.print("\tLaser right: ");
    Serial.print(digitalRead(laser_right));
  */

  Serial.print("\tlidar/laser"); Serial.print(millis()-startTime);
  pressure = PRESSURE_SLOPE * ((float)analogRead(transducer) + BIAS) ;
  /*
    Serial.print("Pressure");
    Serial.print(":\t");
    Serial.print(pressure);
    Serial.print("psi");
  */
  Serial.print("\tpressure"); Serial.print(millis()-startTime);
  //Serial.print("\ttemperatures:");
  for (int x = 0; x < 2; x++)
  {
    digitalWrite(bit4, x);
    for (int y = 0; y < 2; y++)
    {
      digitalWrite(bit2, y);
      for (int z = 0; z < 2; z++)
      {
        digitalWrite(bit1, z);
        float temperature = (float(analogRead(temp)) * 3.3 / 1024 - 0.5) * 1000 / 19.5;
        //Serial.print(temperature);
        //Serial.print("  ");

      }
    }
  }
  Serial.print("\ttemp"); Serial.print(millis()-startTime);
  Serial.println();


}
