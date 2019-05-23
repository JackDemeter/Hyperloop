#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <time.h>
#include <math.h>
#include <Wire.h>
#include "enums.c"
#include "consts.c"


// pin mapping
int network_led = 11;
int safe_led = 12;
int power_led = 13;
int brake = 10;
int motor = 9;


// create a 32 byte packet for transferring data
byte packet[34];

//index to data rules
bool brakeState, motorState, canLaunch;

int currentSpeed = 0;
//
state currentState = SAFE;
faultType currentFault = NONE;


// Create IMU device classes
Adafruit_BNO055 bno1 = Adafruit_BNO055(55, 0x28);
Adafruit_BNO055 bno2 = Adafruit_BNO055(55, 0x29);







void calcTelemetry()// float values[10])
{
  // udpate the given list to include any specs about the speed and distance travelled
  ;
}


void establishInternal() {
  bool internalConnection = false;
  while (internalConnection == false)
  {
    // If the chip receives a command
    if (Serial3.available() > 0)
    {
      char data = Serial3.read();
      if (data == 'A')
      {
        Serial3.write('B');
        internalConnection = true;
      }
    }
    digitalWrite(network_led, HIGH);
    delay(100);
    digitalWrite(network_led, LOW);
    delay(900);
  }
  Serial.println("Internal connection made!");
}

void establishExternal() {
  bool internalConnection = false;
  while (internalConnection == false)
  {
    // If the chip receives a command
    if (Serial3.available() > 0)
    {
      char data = Serial3.read();
      if (data == 'C')
      {
        internalConnection = true;
      }
    }
    digitalWrite(network_led, HIGH);
    delay(100);
    digitalWrite(network_led, LOW);
    delay(100);
    digitalWrite(network_led, HIGH);
    delay(100);
    digitalWrite(network_led, LOW);
    delay(700);
  }
  Serial.println("External connection made!");
}


void IMU_setup()
{
  int reset_IMU = 2;
  pinMode(reset_IMU, OUTPUT);
  digitalWrite(reset_IMU, HIGH);
  delay(500);
  digitalWrite(reset_IMU, LOW);
  delay(1000);
  digitalWrite(reset_IMU, HIGH);



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






float* updateSensors(int cycle)
{
  /* Get a new sensor event */
  sensors_event_t event1;
  bno1.getEvent(&event1);


  sensors_event_t event2;
  bno2.getEvent(&event2);



  // TODO: cycle changes the multiplexer value before grabbing data


  float *list = new float[SENSORS];
  /* Display the floating point data */
  list[GYRO_X1] = event1.orientation.x;
  list[GYRO_Y1] = event1.orientation.y;
  list[GYRO_Z1] = event1.orientation.z;
  list[GYRO_X2] = event2.orientation.x;
  list[GYRO_Y2] = event2.orientation.y;
  list[GYRO_Z2] = event2.orientation.z;
  list[TEMP1] = bno1.getTemp();
  list[TEMP2] = bno2.getTemp();

  imu::Vector<3> accel1 = bno1.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  /* Display the floating point data */
  list[ACCEL_X1] = accel1.x();
  list[ACCEL_Y1] = accel1.y();
  list[ACCEL_TOTAL1] = sqrt(pow(list[ACCEL_X1], 2) + pow(list[ACCEL_Y1], 2));

  imu::Vector<3> accel2 = bno2.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  list[ACCEL_X2] = accel2.x();
  list[ACCEL_Y2] = accel2.y();
  list[ACCEL_TOTAL2] = sqrt(pow(list[ACCEL_X2], 2) + pow(list[ACCEL_Y2], 2));


  return list;
}


void updateIndicators(state temp)
{
  switch (temp) {
    case MOUNT:
      {
        canLaunch = false;
        //brakes and motors off
        brakeState = true;
        motorState = false;
        //Transitions when button is manually pressed
        //if (mountButtonPressed)
        //currentState = SAFE;
        break;
      }
    case RTL:
      {
        //prepare to launch
        motorState = 1;
        canLaunch = true;
        break;
      }
    case SAFE:
      {
        //brakes applied, motor off
        brakeState = false;
        motorState = false;
        canLaunch = false;
        //if (mountButtonPressed)
        //state = MOUNT;
        break;
      }
    case LAUNCH:
      {
        if (canLaunch) {
          //do launch stuff
          motorState = 1;
          brakeState = 1;
          //set motor speeds/accelerate
        }
        else {
          currentState = FAULT;
          currentFault = RTL_SKIP;
        }
        /*
          if (currentSpeed > someValue) { //or distance says stop
          currentState = COAST;
          }
        */
        break;
      }
    case COAST:
      {
        //do coasting stuff
        //maintain speed
        if (currentSpeed = 0) {
          currentState = CRAWL;
        }
        /*
          if (distanceLeft < someValue) {
          currentState = BRAKE;
          }
        */
        break;
      }
    case BRAKE:
      {
        //do achey breaky stuff
        break;
      }
    case CRAWL:
      {
        //these wounds will never heal
        break;
      }
    case FAULT:
      {
        //oops
        break;
      }
    default:
      {
        currentState = FAULT;
      }
  }
}

void updateParameters(state temp)
{
  switch (temp) {
    case MOUNT:
      {
        canLaunch = false;
        //brakes and motors off
        brakeState = true;
        motorState = false;
        //Transitions when button is manually pressed
        //if (mountButtonPressed)
        //currentState = SAFE;
        break;
      }
    case RTL:
      {
        //prepare to launch
        motorState = 1;
        canLaunch = true;
        break;
      }
    case SAFE:
      {
        //brakes applied, motor off
        brakeState = false;
        motorState = false;
        canLaunch = false;
        //if (mountButtonPressed)
        //state = MOUNT;
        break;
      }
    case LAUNCH:
      {
        if (canLaunch) {
          //do launch stuff
          motorState = 1;
          brakeState = 1;
          //set motor speeds/accelerate
        }
        else {
          currentState = FAULT;
          currentFault = RTL_SKIP;
        }
        /*
          if (currentSpeed > someValue) { //or distance says stop
          currentState = COAST;
          }
        */
        break;
      }
    case COAST:
      {
        //do coasting stuff
        //maintain speed
        if (currentSpeed = 0) {
          currentState = CRAWL;
        }
        /*
          if (distanceLeft < someValue) {
          currentState = BRAKE;
          }
        */
        break;
      }
    case BRAKE:
      {
        //do achey breaky stuff
        break;
      }
    case CRAWL:
      {
        //these wounds will never heal
        break;
      }
    case FAULT:
      {
        //oops
        break;
      }
    default:
      {
        currentState = FAULT;
      }
  }
}

















void setup(void)
{
  // set pin modes for indicators
  pinMode(power_led, OUTPUT);
  pinMode(network_led, OUTPUT);
  pinMode(safe_led, OUTPUT);
  pinMode(brake, OUTPUT);
  pinMode(motor, OUTPUT);

  // initiate default state on start up
  currentState = SAFE;
  brakeState = false;
  motorState = false;
  canLaunch = false;

  /* Initialise the sensor, uupon failture cause the power button to blink twice to indicate */
  if (!bno1.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    while (1)
    {
      digitalWrite(power_led, HIGH);
      delay(200);
      digitalWrite(power_led, LOW);
      delay(200);
      digitalWrite(power_led, HIGH);
      delay(200);
      digitalWrite(power_led, LOW);
      delay(1000);
    }
  }



  // Indicate that the pod is on at all times with the power_led
  digitalWrite(power_led, HIGH);
  // Default to the network not connecting and indicate
  digitalWrite(network_led, LOW);
  // pod is set to not safe to approach, which ensures proper boot up into STA.
  digitalWrite(safe_led, LOW);

  delay(1000);

  bno1.setExtCrystalUse(true);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial3.begin(115200);  // start serial for output


  // boot up internal processes, including sensors and internal connections
  establishInternal();
  IMU_setup();






  establishExternal();
  // establishExternal();
  // Connections are set and the network is now properly working.
  digitalWrite(network_led, HIGH);

}






void loop(void)
{
  updateIndicators(currentState);
  updateParameters(currentState);
  calcTelemetry();
  //  // benchmark speed
  //  // int newTime = millis();
  //  digitalWrite(network_led, LOW);
  //  float *list;
  //  list = updateSensors(0);
  //  float accel = list[ACCEL_TOTAL];
  //  /*
  //  Serial.print("Acceleration is: ");
  //  Serial.print(accel);
  //  Serial.println("");
  //  */
  //
  //
  //  if (!canLaunch) digitalWrite(safe_led,HIGH);
  //  else digitalWrite(safe_led,LOW);
  //
  //
  //  digitalWrite(motor,motorState);
  //  digitalWrite(brake, brakeState);
  //  // Serial.println(millis() - newTime);

}
