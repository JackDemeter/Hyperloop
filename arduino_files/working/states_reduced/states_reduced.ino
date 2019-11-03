#include <stdint.h>
#include <stdbool.h>

#include "enums.c"
#include "states_reduced.h"
#include "consts.c"

struct StateDetails
{
  const bool brake;
  const bool motor;
  const bool led_indicator;
};

// represent how the arduino should allow motor, brake and led operation for all states (except fault)
StateDetails States[state::STATES] = {{true, false, true}, {true, false, false}, {false, true, true}, 
{false, true, true}, {false, true, true}, {true, false, true}, {false, true, true}};

// Network Data
char telemetry[PACKET_SIZE];

/****     PIN LAYOUT      ****/
int reset_IMU = 2;
int statePin = 3;
int lidar_trigger = 7;
int lidar_monitor = 8;

int network_led = 11;
int safe_led = 12;
int power_led = 13;
// multiplexer addresses
int bit1 = 22;
int bit2 = 23;
int bit4 = 24;
int RTL_switch = 26;
int RTL_switch_reset = 27;

int brake = 30; // blue wire
int motor = 34;
int relay_controller = 36;

int laser_left = 40;
int laser_right =41;

int temp = A0;
int transducer = A7;

// pressure transducer data
float pressure;
unsigned long pulseWidth;

int networkState;
bool initialBrake;

// Create current/previous states allows for one shot programming later in the code
state currentState, prevState;
// Time State initiated, used for time based thresholding
unsigned long TSI;
// the time that the loop initiated
unsigned long startTime;

void setup(void)
{
  // set pin modes for indicators
  pinMode(power_led, OUTPUT);
  pinMode(network_led, OUTPUT);
  pinMode(safe_led, OUTPUT);
  pinMode(brake, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(RTL_switch, INPUT);
  pinMode(RTL_switch_reset, OUTPUT);
  pinMode(relay_controller, OUTPUT);
  pinMode(lidar_trigger, OUTPUT); // Set pin 2 as trigger pin
  pinMode(lidar_monitor, INPUT); // Set pin 3 as monitor pin
  pinMode(laser_left, INPUT);
  pinMode(laser_right, INPUT);
  pinMode(transducer, INPUT);
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit4, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(laser_left, INPUT);
  pinMode(laser_right, INPUT);
  
  // initiate default state on start up
  networkState = state::STA;
  currentState = state::STA;
  prevState = state::STATES;
  // Indicate that the pod is on at all times with the power_led
  digitalWrite(power_led, HIGH);
  // Default to the network not connecting and indicate
  digitalWrite(network_led, LOW);
  // pod is set to not safe to approach, which ensures proper boot up into STA.
  digitalWrite(safe_led, LOW);
  //Initialize sensor data
  digitalWrite(relay_controller, LOW);
  digitalWrite(lidar_trigger, LOW); // Set trigger LOW for continuous read
 
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // TODO reset fault switch
  
  delay(1000);
  Serial3.begin(115200);  // start serial for output

  // boot up internal processes, including sensors and internal connections
  establishInternal();
  establishExternal();
  // Connections are set and the network is now properly working.
  digitalWrite(network_led, HIGH);
}


void loop(void)
{
  startTime = millis();
  /**** CHECK PHASE ****/
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
  pressure = PRESSURE_SLOPE * ((float)analogRead(transducer) + BIAS) ;
  // Cycle through all temperatures
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
      }
    }
  } 

  // TODO check sensor data
  // TODO calculations
  // ensure pod is within thresholds, otherwise cause a fault and report error

  if (Serial3.available() > 0)
  {
    networkState = (int)Serial3.read(); // convert the character to a integer
    Serial.print(networkState);
  }
  /**** STATE PHASE ****/
  if (networkState == state::FAULT) currentState = state::FAULT; // fault pod upon network request

  // record start time change
  if (currentState != prevState)
  {
    // make if statement one shot
    prevState = currentState;
    // reset time state initialized
    TSI = millis();
    // set related outputs
    digitalWrite(brake, !States[currentState].brake);
    digitalWrite(motor, States[currentState].motor);
    digitalWrite(safe_led, States[currentState].led_indicator);

    // one shot per case
    switch (currentState)
    {
      case (state::STA):
        Serial.println("resetting switch");
        digitalWrite(RTL_switch_reset, HIGH);
        delay(100);
        digitalWrite(RTL_switch_reset, LOW);
        digitalWrite(relay_controller, LOW);
        break;
        
      case (state::RTL):
        initialBrake = true;
        digitalWrite(relay_controller, HIGH);
        break;
      case (state::LAUNCH):
        break;
      case (state::COAST):
        break;
      case (state::BRAKE):
        break;
      case (state::CRAWL):
        break;
      default:
        digitalWrite(relay_controller, LOW);
        break;
    }

    // Record time that state is entered (debugging only)
    printState(currentState);
    Serial.print(" entered at time ");
    Serial.println(TSI);
  }

  // check state (switch case)
  switch (currentState)
  {
    case (state::STA):
      {
        if (digitalRead(RTL_switch) && networkState == state::RTL)
        {
          currentState = state::RTL;
        }
        if (!digitalRead(RTL_switch))
        {
          // reset RTL switch while the switch is off to ensure the pod does not go immediately to RTL when turned on
          networkState = state::STA;
        }
        break;
      }
    case (state::RTL):
      {
        if (networkState == state::LAUNCH)
        {
          currentState = state::LAUNCH;
        }
        break;
      }
    case (state::LAUNCH):
      {
        // 10 second launch phase
        if (millis() - TSI < 9800)
        {
          digitalWrite(safe_led, (millis() / 500) % 2); //Blink indicating launch is about to occur
        }
        else if (millis() - TSI < 10000)
        {
          digitalWrite(safe_led, HIGH); //set high for actual launch
        }
        // run motors
        else
        {
          ; // TODO launch the pod based on TSI and velocity function
        }
        if (networkState == state::COAST)currentState = state::COAST;
        if (networkState == state::BRAKE)currentState = state::BRAKE;
      }
      break;
    case (state::COAST):
      if (millis() - TSI > 10000) // 10 second launch phase
      {
        currentState = state::BRAKE;
      }
      break;
    case (state::BRAKE):
      if (!initialBrake)
      {
        //TODO brake and stay halted
        currentState = state::STA;
      }
      if (millis() - TSI > 10000 && initialBrake) // 10 second launch phase
      {
        currentState = state::CRAWL;
        initialBrake = false;
      }
      break;
    case (state::CRAWL):
      if (millis() - TSI > 10000) // 10 second launch phase
      {
        currentState = state::BRAKE;
      }
      break;

    default:
      // fault occurs, use while loop to send data back
      digitalWrite(brake, !States[currentState].brake);
      digitalWrite(motor, States[currentState].motor);
      digitalWrite(safe_led, States[currentState].led_indicator);
      digitalWrite(relay_controller, LOW);
      break;
  }

  /**** NETWORK PHASE ****/

  telemetry[0] = TEAM_ID;
  telemetry[1] = (byte)currentState;
  // todo add remaining data
  for (int i = 2; i < PACKET_SIZE; i = i + 4)
  {
    //dataToBEBytes(telemetry[i], data?);
    // temp set all data to 0
    for (int n = 0; n < 4; n++)
    {
      telemetry[i + n] = 0;
    }
  }

  // send packet to NA via serial comm
  for (int i = 0; i < PACKET_SIZE; i++)
  {
    Serial3.write((char)telemetry[i]);
    Serial.write(telemetry[i]);
  }
  Serial3.write((byte)0x4); // send end of transmission byte
  Serial3.flush();
}

void establishInternal() {
  bool connection = false;
  while (!connection)
  {
    // If the chip receives a command
    if (Serial3.available() > 0)
    {
      char data = Serial3.read();
      if (data == 'A')
      {
        connection = true;
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
  bool connection = false;
  while (!connection)
  {
    // If the chip receives a command read data and check for predetermined character
    if (Serial3.available() > 0)
    {
      char data = Serial3.read();
      if (data == 'C')
      {
        connection = true;
      }
    }
    // Blink lights while waiting
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

void printState(state s)
{
  switch (s)
  {
    case (state::STA):
      Serial.print("STA");
      break;
    case (state::RTL):
      Serial.print("RTL");
      break;
    case (state::LAUNCH):
      Serial.print("Launch");
      break;
    case (state::COAST):
      Serial.print("Coast");
      break;
    case (state::BRAKE):
      Serial.print("Brake");
      break;
    case (state::CRAWL):
      Serial.print("Crawl");
      break;
    default:
      Serial.print("Fault");
      break;
  }
}
