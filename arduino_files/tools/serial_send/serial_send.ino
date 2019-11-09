// Serial Read
const int PACKET_SIZE = 26;

char telemetry[PACKET_SIZE];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < PACKET_SIZE; i++)
  {
    telemetry[i] = (char)(i+'A');
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < PACKET_SIZE; i++)
  {
    Serial.write((char)telemetry[i]);
  }
  Serial.write((byte)0x4); // send end of transmission byte
  Serial.flush();
  
}
