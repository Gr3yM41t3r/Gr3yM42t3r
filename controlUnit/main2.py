# Importing Libraries
import serial
import time
import time
import csv

arduino = serial.Serial(port='/dev/ttyUSB1', baudrate=9600, timeout=.1)


def write_read(x):
    time.sleep(0.05)
    data = arduino.readline()
    return data


response = False
with open("out.csv", "w") as outputData:
    writer = csv.writer(outputData)
    data=[]
    while True:
            while arduino.inWaiting() > 0:
                data.clear()
                value = arduino.readline().decode('utf-8')
                print(value)
                if len(value.split(";"))>3:
                    a=int(value.split(";")[3])
                    print(value.split(";")[1])
                    print(str(a))
                    data.append(int(value.split(";")[1]))
                    data.append(a)
                    writer.writerow(data)

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
