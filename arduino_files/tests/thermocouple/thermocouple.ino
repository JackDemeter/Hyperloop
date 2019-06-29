/*  Thermocouple testing code
 *  Queen's Hyperloop Design Team
 *  code sets the A5 and A6 to read the values 
 *  the thermalcouples should be run in parallel with a Xk resistor  
 *  Adjust the SLOPE and BIAS to map the data
 */

// adjust these values for calibration
const int SLOPE = 1;
const int BIAS = 0;

int thermocouple_1 = A5;
int thermocouple_2 = A6;

float temp[2];

void setup() {
  // put your setup code here, to run once:
  pinMode(thermocouple_1, INPUT);
  pinMode(thermocouple_2, INPUT);
  
  Serial.begin(9600); // set up a serial monitor for writing analog values
}

void loop() 
{
  // put your main code here, to run repeatedly:
  temp[0] = SLOPE * ((float)analogRead(thermocouple_1)/204) + BIAS;
  temp[1] = SLOPE * ((float)analogRead(thermocouple_2)/204) + BIAS;
  Serial.print("Temperature of thermocouple");
  Serial.print(":\t");
  Serial.print(temp[0] - temp[1]);
  Serial.print("\t\t");
  Serial.println();
}
