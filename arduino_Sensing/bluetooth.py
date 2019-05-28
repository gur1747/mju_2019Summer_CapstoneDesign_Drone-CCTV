#! /usr/bin/python

import serial
from time import sleep

bluetoothSerial = serial.Serial("/dev/rfcomm0", baudrate=9600)

while not done:
	
	data = float(bluetoothSerial.readline())

	if(data == 0):
		print "location1: danger_object"
        location = 1

	if(data == 1):
		print "location1: danger_gas"
        location = 1

	if(data == 2):
		print "location2: danger_gas"
        location = 2

	if(data == 3):
		print "location3: danger_gas"
        location = 3
		
	if(data == 4):
		print "location4: danger_gas"
        location = 4

serial.close();
print "Bye!"