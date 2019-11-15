#include <stdint.h>
#include <stdbool.h>

#include "enums.c"
//#include "states_reduced.h"
#include "consts.c"

/**************************************************************
 * Constants defined to replace parameters for testing purposes
 **************************************************************/

 #define IMU_speed
 #define motor_current_thresh_peak 250 //amps
 #define motor_current_thresh_cont 200//Amps
 #define motor_voltage_thresh 50.4  //V
 #define battery_temp_thresh 60  //degress C
 #define motor_temp_thresh 180 //degrees C
 #define battery_pressure_thresh 10 //psi


 #define IMU_speed
 #define motor_current_peak 250 //amps
 #define motor_current_thresh_cont 200//Amps
 #define motor_voltage_thresh 50.4  //V
 #define battery_temp_thresh 60  //degress C
 #define motor_temp_thresh 180 //degrees C
 #define battery_pressure_thresh 10 //psi
 

 

struct StateDetails
{
  const bool brake;
  const bool motor;
  const bool led_indicator;
};

// represent how the arduino should allow motor, brake and led operation for all states (except fault)
//StateDetails States[state::STATES] = {{true, false, true}, {true, false, false}, {false, true, true}, 
//{false, true, true}, {false, true, true}, {true, false, true}, {false, true, true}};

// Network Data
//char telemetry[PACKET_SIZE];

/****     PIN LAYOUT      ****/
int led_0 = 2;
int led_1 = 3;
int led_2 = 4;

int RTL_switch = 7;



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
  pinMode(RTL_switch, INPUT);
//  pinMode(RTL_switch_reset, OUTPUT);

  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  pinMode(RTL_switch, INPUT);

  //init all lights to high
  digitalWrite(led_0, HIGH);
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  
  // initiate default state on start up
//  networkState = state::STA;
  currentState = state::STA;
  prevState = state::STATES;
 
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // TODO reset fault switch
  Serial3.begin(115200);
  Serial3.println("Orientation Sensor Test"); Serial.println("");
  while (!Serial3) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //
  
  delay(1000);
//  dispState(state::LAUNCH);
  for(int i = 0; i <= state::STATES; i++) {
    dispState(i);
    delay(500);
  }
}


void loop(void) {
  int state = getSerialState();
  if (state >= 0) dispState(state);
}

int getSerialState()
{
  char receivedChar;
  if (Serial3.available())
  {
    
    receivedChar = Serial3.read();
    int state =((int)receivedChar - (int)'0');
    Serial.print(state);
    return state;
  }
  return -1;
}

void getCurrentState()
{
  if(Serial.available()) {
    char input = Serial.read();
    if ( '0' < input && input < '0' + state::STATES)
    {
      currentState = (state)((int)input - (int)'0');
      dispState(currentState);
      printState(currentState);
    }
  }
}

void dispState(int s) {
//  Serial.print("%d %d %d", s&0x1, s&0x2, s&0x4);
// Print bit data for testing
/*
  Serial.print(s&0x1);
  Serial.print(s&0x2);
  Serial.print(s&0x4);
  */
  digitalWrite(led_0, s&0x1);
  digitalWrite(led_1, s&0x2);
  digitalWrite(led_2, s&0x4);
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
