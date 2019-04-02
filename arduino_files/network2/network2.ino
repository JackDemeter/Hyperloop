#include <Wire.h>



int button = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  establishInternal();  // send a byte to establish contact until receiver responds
  establishExternal();
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(button));
  ;
}

void establishInternal() {
  int requestNumber = 0;
  char receivedChar = ' ';

  // Request the state arduino to send a signal, continue to request signal until the 'A' signal is recieved.
  while (receivedChar != 'B') {
    
//    Serial.print("Request Number: ");
//    Serial.print(requestNumber);
    Serial.write('A');
    if (Serial.available())
    {
      receivedChar = Serial.read();
//      Serial.print("\tCharacter: ");
//      Serial.print(receivedChar);
    }
//    Serial.println("");
    delay(500);
    requestNumber++;
  }
//  Serial.println("connected");
  digitalWrite(13,HIGH);
}


void establishExternal() {
  // TODO, replace this with actual network data
  while (digitalRead(button) == LOW);
  Serial.write('C');
  digitalWrite(13,LOW);
}
