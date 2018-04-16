#!/bin/python3 

import sys
from time import sleep
from time import asctime

abs_position_of_detector = 0

def init():
    print(asctime()+" Init script was loading")
    return

# relitive position motion detector
def r_motion_detector_z(pos):
    motion_detector(pos+abs_position_of_detector)
    return

# absolutly position motion detector
def motion_detector_z(pos):
    print("detector move to "+str(pos))
    return

def begin_measuring(value):

    sleep(value)
    return

init()

# EOF

