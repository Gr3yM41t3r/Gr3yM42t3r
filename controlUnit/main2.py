# Importing Libraries
import serial
import time
import time

arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)


def write_read(x):
    time.sleep(0.05)
    data = arduino.readline()
    return data


response = False

while True:

        while arduino.inWaiting() > 0:
            value = arduino.readline().decode('utf-8')
            print(value)
            if value == "received":
                response = True
            elif value =="node is unreacheable":
                response = True
                print("ERROR-------------------------")

"""
    while not response:
        print("wi3")
        value = arduino.readline().decode('utf-8')
        print(value)  # printing the value
        print(value == "received")
        print("wi32")
        if value == "received":
            response = True#"""
