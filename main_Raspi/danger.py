#! /usr/bin/python
import socket
import time
import serial
from time import sleep

host = "192.168.43.151"
port1 = 8886
port2 = 8888

bluetoothSerial = serial.Serial("/dev/rfcomm0", baudrate=9600)

server1_sock = socket.socket(socket.AF_INET)
server1_sock.bind((host, port1))
server1_sock.listen(1)

server2_sock = socket.socket(socket.AF_INET)
server2_sock.bind((host, port1))
server2_sock.listen(1)

print("waiting android")
client1_sock, addr1 = server1_sock.accept()
print("Connected by client1", addr1)
client2_sock, addr1 = server2_sock.accept()
print("Connected by client2", addr2)

temp = 0
location= 0

while not done:
   
   temp = location
   data = 0
   data = float(bluetoothSerial.readline())

   if(data == 0):
      #print "location1: danger_object"
        location = 1

   if(data == 1):
      #print "location1: danger_gas"
        location = 1

   if(data == 2):
      #print "location2: danger_gas"
        location = 2

   if(data == 3):
      #print "location3: danger_gas"
        location = 3
      
   if(data == 4):
      #print "location4: danger_gas"
        location = 4
   
   if(temp != location):
      print location
      client1_sock.send(str(location))
      client2_sock.send(str(location))

client1_sock.close()
server1_sock.close()
client2_sock.close()
server2_sock.close()

serial.close();
print "Bye!"
