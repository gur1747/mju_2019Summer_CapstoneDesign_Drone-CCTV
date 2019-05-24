#! /usr/bin/python

import serial
from time import sleep

bluetoothSerial = serial.Serial("/dev/rfcomm0", baudrate=9600)

while not done:
	
	data = float(bluetoothSerial.readline())

	if(100>data>=28):
		print "danger_object: "
		temp=data;
	if(data>=500):
		print "danger_gas: "
		gas=data;

	print data

serial.close();
print "Bye!"