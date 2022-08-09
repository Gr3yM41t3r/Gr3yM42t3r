from numpy import size
import serial
import time

arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)


def read_read():
    time.sleep(0.05)
    data = arduino.readline()
    return data



while True:
    while arduino.inWaiting() > 0:
        value = arduino.readline().decode('utf-8')
        value = value.strip()
        if(len(value)==5):
            pass
        else:
            print(value)
            add_one_record(value.split(";")[0],value.split(";")[1],value.split(";")[2],value.split(";")[3],value.split(";")[4],value.split(";")[5])
            print(value)

    

