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
int IMU_reset = 2;

// create a 32 byte packet for transferring data
byte packet[34];

//index to data rules
bool brakeState, motorState, canLaunch;

int currentSpeed = 0;
//
state currentState = SAFE;
faultType currentFault = NONE;


Adafruit_BNO055 bno1 = Adafruit_BNO055(55);


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

  establishInternal();
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


void calcTelemetry(float values[10])
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

float* updateSensors(int cycle)
{
  // TODO: cycle changes the multiplexer value before grabbing data
  /* Get a new sensor event */
  sensors_event_t event;
  bno1.getEvent(&event);

  float *list = new float[7];


  /* Display the floating point data */
  list[0] = event.orientation.x;
  list[1] = event.orientation.y;
  list[2] = event.orientation.z;
  list[3] = bno1.getTemp();

  imu::Vector<3> accel = bno1.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  /* Display the floating point data */
  list[4] = accel.x();
  list[5] = accel.y();
  list[6] = sqrt(pow(accel.x(), 2) + pow(accel.y(), 2));


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
