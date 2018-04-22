#!/bin/python3 

import sys
from time import sleep
from time import asctime

abs_position_of_detector = 0

def init():
    abs_postion_of_detector = 2  # get from tango!!!
    
    print(asctime()+" Init script was loading")
    return

# relitive position motion detector
def r_motion_detector_z(pos):
    motion_detector_z(pos+abs_position_of_detector)
    return

# absolutly position motion detector
def motion_detector_z(pos):
    print("detector move to "+str(pos))
    abs_pos_of_detector = pos   # and get from tango or compare
    return

def begin_measuring(value):

    sleep(value)
    return

init()

# EOF

