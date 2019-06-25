#define PACKET_SIZE 34

#include <Ethernet.h>
#include <EthernetUdp.h>

byte packet[PACKET_SIZE];

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


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE
};
const IPAddress ip(192, 168, 8, 20);
const IPAddress server(192, 168, 8, 1);
const IPAddress computer(192, 168, 8, 10);
const unsigned int localPort = 3000;      // local port to listen on

void setup() {

  // clean all packets
  zeroPacket(packet, PACKET_SIZE);


  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet
  Ethernet.begin(mac, ip);
  // prevent sending data to both IPs from causing effecting message frequency
  Ethernet.setRetransmissionCount(1);
  Ethernet.setRetransmissionTimeout(10);

  // Open serial communications and wait for port to open:
  
  Serial.begin(115200);
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
  Serial.println();
  
}

void loop() 
{
  sendUDP(packet, PACKET_SIZE, server, 3000);
  sendUDP(packet, PACKET_SIZE, computer, 3000);
}
