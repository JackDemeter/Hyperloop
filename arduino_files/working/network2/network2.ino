#include <Ethernet.h>
#include <EthernetUdp.h>

const int LAPTOP_IP = 10;
const int PACKET_SIZE = 34;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 20);
unsigned int localPort = 3000;      // local port to listen on

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

byte spaceXPacket[PACKET_SIZE];
byte telemetry[PACKET_SIZE];

void zeroPacket(byte *packet, int bytes)
{
  // sets all packets to zero for start
  for (int i = 0; i < bytes; i++)
  {
    packet[i] = 0;
  }
}

void sendUDP(byte *packet, int packetSize, String IP, int port)
{
  // send the packet to an address/port of choice
  Udp.beginPacket(&IP, 3000);
  for (int i = 0; i < packetSize; i++) Udp.write(packet[i]);
  Udp.endPacket();
}


void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for native USB port only

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    //Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    //Serial.println("Ethernet cable is not connected.");
  }

  // start UDP
  Udp.begin(localPort);

  establishInternal();  // send a byte to establish contact until receiver responds

  establishExternal();
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(button));
  int packetCheck = Udp.parsePacket();
  if (packetCheck && Udp.remoteIP()[3] == LAPTOP_IP)
  {
    int packet = Udp.read();
    Serial.write((byte)packet); // convert the signal to int

  }
  if (Serial.available())
  {
    int bytes = Serial.readBytesUntil((char)0x4, telemetry, 33);
  }
  for (int i = 0; i < 14; i++) 
  {
    // Send team_id through to velocity from telemetry to spaceXpacket
    spaceXPacket[i] = telemetry[i];
  }
  sendUDP(spaceXPacket, PACKET_SIZE, (String)"192.168.0.1", 3000);
  sendUDP(telemetry, PACKET_SIZE, (String)"192.168.0.10", 3000);
}

void establishInternal() {
  int requestNumber = 0;
  char receivedChar = NULL;

  // Request the state arduino to send a signal, continue to request signal until the 'A' signal is recieved.
  while (receivedChar != 'B') {

    Serial.write('A');
    if (Serial.available())
    {
      receivedChar = Serial.read();
    }

    delay(500);
    requestNumber++;
  }
  digitalWrite(13, HIGH);
}


void establishExternal() {
  // TODO, replace this with actual network data
  // if there's data available, read a packet
  int packet_size = Udp.parsePacket();
  int packet = Udp.read();
  bool connection = false;
  while (!connection)
  {
    if (packet_size == 1 && Udp.remoteIP()[3] == LAPTOP_IP)
    {
      // A connection has been established with the computer
      /*
        Serial.print("From ");
        IPAddress remote = Udp.remoteIP();
        for (int i=0; i < 4; i++) {
        Serial.print(remote[i], DEC);
        if (i < 3) {
          Serial.print(".");
        }
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());
      */
      Serial.write('C');
      digitalWrite(13, LOW);
      connection = true;
    }
    packet_size = Udp.parsePacket();
  }
}
