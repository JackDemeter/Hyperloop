// Serial Write
int counter = 0;
char telemetry[33];
void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial3.available())
  {
    int bytes = Serial3.readBytesUntil((char)0x4, telemetry, 33);
    for (int i = 0; i < bytes;  i++)
    {
      Serial.print(telemetry[i]);
    }
    Serial.println();
  }
}
