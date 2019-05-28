#! /usr/bin/python

import serial
from time import sleep

bluetoothSerial = serial.Serial("/dev/rfcomm0", baudrate=9600)

temp = 0
location= 0

while not done:
	
	temp = location

	data = float(bluetoothSerial.readline())

	if(data == 0):
		//print "location1: danger_object"
        location = 1

	if(data == 1):
		//print "location1: danger_gas"
        location = 1

	if(data == 2):
		//print "location2: danger_gas"
        location = 2

	if(data == 3):
		/print "location3: danger_gas"
        location = 3
		
	if(data == 4):
		//print "location4: danger_gas"
        location = 4
	
	if(temp != location):
		print location

serial.close();
print "Bye!"