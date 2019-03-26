
/*The various states are as follows
0 - Mounting
1 - Safe to Approach
2 - Lanching
3 - slowing to 50 and maintaining it
4 - braking
5 - crawling
6 - end of run
7 - fault
*/


/*
 * Interrupt code looks like as follows (For a port)

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}


 */

 
//on startup will be in mounting
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
};

enum faultType
{
  NONE,
  SETUP,
  COMM_NETWORK_LOSS,
  COMM_ARDUINO_LOSS,
  RTL_SKIP,
}


state currentState = SAFE;
faultType currentFAULT = NONE;
//index to data rules
bool brakeState, motorState;
//Since there's two motors, need to make sure they're the same speed (Calibration)
int motor1Speed, motor2Speed;


bool mountButtonPressed = true;
bool canLaunch = false;

//todo, write a packet to send data to networking Arduino
String commWithNetwork(){
  //for SpaceX team_id, status, acceleration, position, velocity
  String buildPacket = "Queen's " + status + ", " + acceleration + ", " + position + ", " + velocity;
  return buildPacket;
}

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
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(currentState){
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
      if(canLaunch){
      //do launch stuff
        motorState = 1;
        brakeState = 1;
        //set motor speeds/accelerate
      }
      else{
        currentState = FAULT;
        currentFault = RTL_SKIP;
      }
      if(currentSpeed > someValue){//or distance says stop
        currentState = COAST;
      }
      break;
    }
    case COAST:
    {
      //do coasting stuff
      //maintain speed
      if(currentSpeed = 0){
        currentState = CRAWL;
      }
      if(distanceLeft < someValue){
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
  


}
