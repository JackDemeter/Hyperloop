
#define transducer A0
#define laserA 
#define laserB
#define bit1 22
#define bit2 23
#define bit4 24
#define temp 
void setup() 
{
  //LIDAR
  pinMode(8, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(8, LOW); // Set trigger LOW for continuous read
  pinMode(9, INPUT); // Set pin 3 as monitor pin  

  //TRANSDUCER
  pinMode(transducer, INPUT);

  //LASER SENSOR
  pinMode(laserA, INPUT)
  pinMode(laserB, INPUT)

  //THERMISTOR
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);
  pinMode(bit4, OUTPUT);
  pinMode(temp, INPUT);

  Serial.begin(9600); // Start serial communications
}

void loop() 
{
  //LIDAR
  pulseWidth = pulseIn(9, HIGH);

  if(pulseWidth != 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
    Serial.println(pulseWidth); // Print the distance
  }

  //TRANSDUCER
  pressure = SLOPE * ((float)analogRead(transducer) + BIAS) ;
  Serial.print("Pressure");
  Serial.print(":\t");
  Serial.print(pressure);
  Serial.print("psi");
  Serial.println();

  //LASER SENSOR
  if(digitalRead(A)==LOW && digitalRead(B)==LOW)
  {
    Serial.println("LO");
  }
  else
  {
    Serial.println("HI");
  }

  //THERMISTOR
  
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
  
}
