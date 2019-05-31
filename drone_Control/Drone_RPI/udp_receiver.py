#udp rcvr - Py

import socket

# socket create
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
recv_address = ('0.0.0.0', 9999)
sock.bind(recv_address)

data_size = 512

data, sender = sock.recvfrom(data_size)
sock.close()
