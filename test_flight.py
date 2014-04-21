import Heli_Python
import time

def main():
    copter = Heli_Python.Heli()
    copter.throttle = 90
    copter.send()
    time.sleep(5)
    copter.land()
    
    
if __name__ == "__main__":
    main()
    
