int button = 2;

int firstSensor = 0;    // first analog sensor
int secondSensor = 0;   // second analog sensor
int thirdSensor = 0;    // digital sensor
int inByte = 0;         // incoming serial byte

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(button));
  
 
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    // read first analog input, divide by 4 to make the range 0-255:
    Serial.write(button);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.write('A');   // send a capital A
    delay(300);
    digitalWrite(13,LOW);
  }
  Serial.println("connected");
  digitalWrite(13,HIGH);
}
