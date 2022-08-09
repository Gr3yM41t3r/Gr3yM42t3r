# Importing Libraries
import serial
import time
import time

arduino = serial.Serial(port='/dev/ttyUSB1', baudrate=9600, timeout=.1)


def write_read(x):
    time.sleep(0.05)
    data = arduino.readline()
    return data


response = False

while True:
    counter2=0
    message = input("type message")
    arduino.write(bytes(message, 'utf-8'))
    response = False
    while not response:
        counter2 += 1
        time.sleep(1)
        print(arduino.inWaiting())
        while arduino.inWaiting() > 0:
            value = arduino.readline().decode('utf-8')
            print(arduino.inWaiting())
            if value == "received":
                response = True
            elif value =="node is unreacheable":
                response = True
                print("ERROR-------------------------")
            elif counter2>10:
                response = True


"""
    while not response:
        print("wi3")
        value = arduino.readline().decode('utf-8')
        print(value)  # printing the value
        print(value == "received")
        print("wi32")
        if value == "received":
            response = True#"""
