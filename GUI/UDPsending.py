import socket


def send_via_udp(MESSAGE):
    UDP_IP = "192.168.8.20"
    UDP_PORT = 3000
    Message_as_bytes = bytes([int(MESSAGE)])

    print("UDP target IP:", UDP_IP)
    print("UDP target port:", UDP_PORT)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP
    sock.connect((UDP_IP, UDP_PORT))
    # send a byte value to the arduino via UDP
    #MESSAGE = bytes([int(input("MESSAGE:"))])
    sock.send(Message_as_bytes)
    print(Message_as_bytes)
    sock.close()

#while(True):
#    send_via_udp(input())
