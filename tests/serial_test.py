#!/usr/bin/env python
import serial, sys, time, os        

def main():
    # path = [x for x in os.listdir('/dev')
            # if x.startswith('tty.usb')][0]
    
    # path = '/dev/'+path
    path = "/dev/cu.usbmodem3d11"
    print("path = ", path)
    serial1 = serial.Serial(path, 9600)
    
    msg = "5"

    time.sleep(2)
    serial1.write(msg)
    serial1.flush()
    print('sent {}'.format(msg))


if __name__ == "__main__":
    main()

