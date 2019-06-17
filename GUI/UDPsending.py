import socket
UDP_IP = "192.168.0.20"
UDP_PORT = 3000
MESSAGE = 0

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP
while(MESSAGE != 9):
    MESSAGE = bytes(int(input("MESSAGE:")))
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))


