/*  Pressure transducer testing code
    Queen's Hyperloop Design Team
    A0 pin to pressure sensor, using 5V and ground
    Adjust the SLOPE and BIAS to map the data
*/

// adjust these values for calibration
const float SLOPE = 0.126;
const float BIAS = -0.5 * 1024 / 5;

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
