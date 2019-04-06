/*   The arduino code for the state arduino

     This code is flashed onto the state arduino and must be updated before each laumch to specify the speed of the pod and other safety parameters


     TODO: make a read me explaining the whole process

*/


// pin mapping


int network_led = 11;
int safe_led = 12;
int power_led = 13;
 


// preset calculated values for when the pod should engage certain aspects
// must be flashed each time to change
// distances are in in meters and speeds are in m/s
const int BRAKE_DIST_THRESH = 800;
const int END_DIST_THRESH = 1000;
// speed that the pod coasts at (~10km/h)
const float COAST_SPEED_THRESH = 2.8;
// Variable value to set the maximum speed of the pod
// max speed that the pod attempts to achieve (~200km/h)
const float LAUNCH_SPEED_THRESH = 55.56;

// Packet data
const uint8_t TEAM_ID = 11;


int podSpeed = 0;
int podDistance = 0;
bool indicator = 0;

enum state
{
  FAULT,
  SAFE,
  RTL,
  LAUNCH,
  COAST,
  BRAKE,
  CRAWL,
  MOUNT,
  STATES
};

enum faultType
{
  NONE,
  SETUP,
  COMM_NETWORK_LOSS,
  COMM_ARDUINO_LOSS,
  RTL_SKIP,
};

// set the state and fault types to none
state currentState = SAFE;
faultType currentFault = NONE;

//index to data rules
bool brakeState, motorState;

//Since there's two motors, needto make sure they're the same speed (Calibration)
int motor1Speed, motor2Speed;
float acceleration = 0;
float velocity = 0;
byte packet[34];

bool mountButtonPressed = false;
bool canLaunch = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  canLaunch = false;
  //while(true){
  //todo:
  //check for networking signal/initialize connection
  //Schedule a timeout, that if timesout, end program
  //}

  //set up sensor ports/serial monitors

  //
  currentState = SAFE;
  brakeState = false;
  motorState = false;


  // set pin modes for indicators
  pinMode(power_led,OUTPUT);
  pinMode(network_led,OUTPUT);
  pinMode(safe_led,OUTPUT);

  // Indicate that the pod is on at all times with the power_led
  digitalWrite(power_led, HIGH);

  // Default to the network not connecting and indicate the pod is not safe to approach, which ensures proper boot up.
  digitalWrite(network_led, LOW);
  digitalWrite(safe_led, LOW);
  
}

void loop() {
  
  
  /*
  // put your main code here, to run repeatedly:
  switch (currentState) {
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
        if (currentSpeed > someValue) { //or distance says stop
          currentState = COAST;
        }
        break;
      }
    case COAST:
      {
        //do coasting stuff
        //maintain speed
        if (currentSpeed = 0) {
          currentState = CRAWL;
        }
        if (distanceLeft < someValue) {
          currentState = BRAKE;
        }
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
  Serial.print("Brakes: ");
  Serial.print(brakeState);
  Serial.print("Motor: ");
  Serial.print(motorState);
  Serial.print("State: ");
  Serial.print(state);

  int list[4] = updateValues();
  Serial.println(list[0] + '\t' + list[1] + '\t' + list[2] + '\t' + list[3] + '\n');
}



//todo, write a packet to send data to networking Arduino
void formPacket() {
  //for SpaceX team_id, status, acceleration, position, velocity
  // unint8_t variables

  packet[0] = TEAM_ID;
  packet[1] = uint8_t(currentState);

  // int32_t variables
  // acceleration
  packet[2] = 2;
  // position
  packet[6] = 2;
  // velocity
  packet[10] = 2;
  // battery voltage
  packet[14] = 0;
  // battery current
  packet[18] = 0;
  // battery temp
  packet[22] = 0;
  // pod temp
  packet[26] = 0;
  // uint32_t
  // stripe count
  packet[30] = 2;

  */
}

int* updateValues()
{
  int *values = new int[5];
  values[0] = 0;
  values[1] = 0;
  values[2] = 0;
  values[3] = 0;
  values[4] = 0;
  return (values);
}
