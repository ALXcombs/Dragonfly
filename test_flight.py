import py_to_copter
import time
import os
#yaw pitch throttle trim

def main():
    copter = py_to_copter.Heli()
    os.system("say 'Take off'")
    copter.hover(1)
    os.system("say 'rising'")
    copter.update_flight_params(63,60,90,0)
    time.sleep(1)
    os.system("say 'forwards'")
    copter.update_flight_params(63,40,90,0)
    time.sleep(1)
    os.system("say 'backward'")
    copter.update_flight_params(63,100,90,0)
    time.sleep(1)
    os.system("say 'landing'")
    copter.land()
    
    
if __name__ == "__main__":
    main()
