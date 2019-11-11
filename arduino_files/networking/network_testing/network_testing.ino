#include <Ethernet.h>
#include <EthernetUdp.h>
// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// network setup
const int LAPTOP_IP = 10;
const int PACKET_SIZE = 34;

const IPAddress ip(192, 168, 8, 20);
const IPAddress server(192, 168, 8, 2);
const IPAddress computer(192, 168, 8, 10);
const unsigned int localPort = 3000;      // local port to listen on

byte spaceXPacket[PACKET_SIZE]; //packet to send spaceX
byte telemetry[PACKET_SIZE];    //packet to send to computer

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

/*  -------------------------------------------------------------------------
    FUNCTIONS
    -------------------------------------------------------------------------
*/
void zeroPacket(byte *packet, int bytes)
{
  // sets all packets to zero
  for (int i = 0; i < bytes; i++)
  {
    packet[i] = 0;
  }
}

void sendUDP(byte *packet, int packetSize, IPAddress IP, int port)
{
  // send the packet to an address/port of choice
  Udp.beginPacket(IP, port);
  for (int i = 0; i < packetSize; i++)
  {
    Udp.write(int(packet[i]));
    // Serial.print(int(packet[i])); // debugging
  }
  // Serial.println(); // debugging

  Udp.endPacket();
}

void updatePacket(byte *packet, int packetSize, byte *updatePacket)
{
  // update the current packet with data from another packet
  for (int i = 0; i < packetSize; i++)
  {
    packet[i] = updatePacket[i];
  }
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
      connection = true;
    }
    packet_size = Udp.parsePacket();
  }
}


/*  -------------------------------------------------------------------------
    MAIN
    -------------------------------------------------------------------------
*/
void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet
  Ethernet.begin(mac, ip);
  // prevent sending data to both IPs from causing effecting message frequency
  Ethernet.setRetransmissionCount(1);
  Ethernet.setRetransmissionTimeout(10);

  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for native USB port only

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    //Serial.println("Ethernet shield was not found.");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }

  // start UDP
  Udp.begin(localPort);

  //establishInternal();  // send a byte to establish contact until receiver responds
  establishExternal();

  zeroPacket(spaceXPacket, PACKET_SIZE);
  zeroPacket(telemetry, PACKET_SIZE);

}



void loop() {
  
  char packet[14];
  char packet_data;
  int packet_size = Udp.parsePacket();
  if (packet_size != 0) {
    packet_data = Udp.read();
    packet[1] = packet_data;
  }
  sendUDP(packet, PACKET_SIZE, server, 3000);
  sendUDP(packet, PACKET_SIZE, computer, 3000);
}
