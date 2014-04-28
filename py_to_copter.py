import serial
import sys
import time
import os

class Heli(object):
    """this sends commands to the arduino to control the helicopter"""

    def __init__(self):
        """Find the serial port and set flight params"""

        #path = [x for x in os.listdir('/dev')
                    #if x.startswith('tty.usb')][0]
        #path = '/dev/'+path
        path = "/dev/cu.usbmodem3d11"
        print("path = ", path)
        self._s = serial.Serial(path, 9600)
        time.sleep(2)

        # Set default flight params
        self.yaw = 63
        self.pitch = 63
        self.throttle = 0
        self.trim = 63

        # Other params
        self.speak = False
        self.log = True


    def update_flight_params(self, yaw, pitch, throttle, trim):
        """this sends commands through the serial port

        this only works in python2 because it uses ascii characters
        instead of the unicode from python3
        """

        self.yaw = yaw
        self.pitch = pitch
        self.throttle = throttle
        self.trim = trim
        msg = [self.yaw, self.pitch, self.throttle, self.trim]
        
        self._s.write(msg)
        self._s.flush()
        if self.log == True:
            print('sent {}'.format(msg))


    def land(self):
        if self.speak == True:
            os.system("say 'Landing'")
        while self.throttle > 35:
            self.throttle = self.throttle - 5
            self.update_flight_params(self.yaw, self.pitch, self.throttle,
                                        self.trim)
            time.sleep(.5)
            self.update_flight_params(63, 63, 0, 63)

    def hover(self, seconds):
        self.update_flight_params(63,60,75,0)
        time.sleep(seconds)

