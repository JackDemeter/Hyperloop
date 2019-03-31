/* This program allows you to try PWM values to the motor controller from 0 - 255
 *  
 *  Use the website below to download the Sproto program for monitoring/adjusting motor settings
 * 
 * https://www.scorpionsystem.com/support/downloads/
 * 
 * AND download the Scorpion V Link 2 Cable, follow the instructions on their site to install proper drivers
 * 
 * Message me (Jack Demeter) if you have any issues!
 */


// the potentiometer plugs attaches here
int pot = A0;
// the pwm to the motorcontroller connects here
int pwm = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(pot, INPUT);
  pinMode(pwm, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int value = analogRead(pot);
  Serial.println(value/4);
  analogWrite(pwm, value/4);
}
