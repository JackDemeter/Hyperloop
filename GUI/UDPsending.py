import socket
UDP_IP = "192.168.0.20"
UDP_PORT = 3000
MESSAGE = 0

def return_one_byte(val):
    if val == 0:
        return b'x\00'
    if val == 1:
        return b'x\01'
    if val == 2:
        return b'x\10'
    if val == 3:
        return b'x\11'
    if val == 4:
        return b'x\04'
    if val == 5:
        return b'x\05'
    if val == 6:
        return b'x\06'
    if val == 7:
        return b'x\07'
    if val == 8:
        return b'x\08'

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP
sock.connect((UDP_IP, UDP_PORT))
while(MESSAGE != 9):
    # send a byte value to the arduino via UDP
    MESSAGE = bytes([int(input("MESSAGE:"))])
    sock.send(MESSAGE)
    print(MESSAGE)
sock.close()