import socket

UDP_IP = "192.168.0.10"
UDP_PORT = 3000

sock = socket.socket(socket.AF_INET, # Internet
                 socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(34) # buffer size is 1024 bytes
    print("received message:", data)