/*
  UDPSendReceiveString:
  This sketch receives UDP message strings, prints them to the serial port
  and sends an "acknowledge" string back to the sender

  A Processing sketch is included at the end of file that can be used to send
  and received messages for testing with a computer.

  created 21 Aug 2010
  by Michael Margolis

  This code is in the public domain.
*/
#define PACKET_SIZE 34

#include <Ethernet.h>
#include <EthernetUdp.h>


// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


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
  Udp.beginPacket(IP, 3000);
  for (int i = 0; i < packetSize; i++) Udp.write(packet[i]);
  Udp.endPacket();
}

void updatePacket(byte *packet, int packetSize, byte *updatePacket)
{
  // update the current packet with data from another packet
  for (int i = 0; i < packetSize; i++)
  {
    packet[i] = updatePacket[i]
  }
}


byte spaceXPacket[PACKET_SIZE];

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 20);

unsigned int localPort = 8888;      // local port to listen on


void setup() {

  // clean all packets
  zeroPacket(spaceXPacket, PACKET_SIZE);


  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start UDP
  Udp.begin(localPort);
}

void loop() {
  
  sendUDP(spaceXPacket, PACKET_SIZE, "192.168.0.1", 3000);
  sendUDP(spaceXPacket, PACKET_SIZE, "192.168.0.10", 3000);
  delay(30);
}
