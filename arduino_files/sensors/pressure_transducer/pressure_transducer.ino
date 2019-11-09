/*  Pressure transducer testing code
    Queen's Hyperloop Design Team
    A0 pin to pressure sensor, using 5V and ground
    Adjust the SLOPE and BIAS to map the data
*/

// adjust these values for calibration


//BIAS 1 for 1/8 inch
//const float SLOPE = 0.125;
//const float BIAS = -1.078 * 1024 / 5;
//const float BIAS = -0.5 * 1024 / 5;

//BIAS 2/3 for 1/4 inch 
const float SLOPE = 0.188;
const float BIAS = -0.49 * 1024 / 5;

//BIAS 4 for 1/8 inch
//const float BIAS = -1.078 * 1024 / 5;

int transducer = A0;

float pressure;

void setup() {
  // put your setup code here, to run once:
  pinMode(transducer, INPUT);

  Serial.begin(9600); // set up a serial monitor for writing analog values
}

void loop()
{
  // put your main code here, to run repeatedly:
  pressure = SLOPE * ((float)analogRead(transducer) + BIAS) ;
  Serial.print("Pressure");
  Serial.print(":\t");
  Serial.print(pressure);
  Serial.print("psi");
  Serial.println();
}
