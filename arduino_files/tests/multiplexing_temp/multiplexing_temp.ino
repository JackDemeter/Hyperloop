/*  Pressure transducer testing code
    Queen's Hyperloop Design Team
    A0 pin to pressure sensor, using 5V and ground
    Adjust the SLOPE and BIAS to map the data
*/

int bit1 = 22;
int bit2 = 23;



int bit4 = 24;
int temp = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit4, OUTPUT);
  pinMode(temp, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int x = 0; x < 2; x++)
  {
    digitalWrite(bit4, x);
    for (int y = 0; y < 2; y++)
    {
      digitalWrite(bit2, y);
      for (int z = 0; z < 2; z++)
      {
        digitalWrite(bit1, z);
        Serial.print((float(analogRead(temp))*3.3/1024-0.5)*1000/19.5);
        Serial.print('\t');
        
      }
    }
  }
  Serial.println();
}
