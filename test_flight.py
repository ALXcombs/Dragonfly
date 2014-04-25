import py_to_copter
import time

def main():
    copter = py_to_copter.Heli()
    copter.update_flight_params(63,63,40,63)
    time.sleep(5)
    copter.land()
    
    
if __name__ == "__main__":
    main()
