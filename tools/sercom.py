#!/usr/bin/env python

# author : Parhusip, Babang Putra
# date   : 29/4/2020


"""To connect to serial comm by using pyserial package.
To install the package:
'python -m pip install pyserial'
Ref: https://pyserial.readthedocs.io/.
"""

import serial
import argparse
import sys
import time

# map of matched strings count
matched_str_cnt = {
        'string_to_match_here': 0,
        }

def get_args():
    """Parse the input argument."""
    parser = argparse.ArgumentParser()

    parser.add_argument("-c", "--comport", required=True,
            help="serial comm port number/device")
    parser.add_argument("-d", "--duration", required=True,
           type=int, help="duration in secs to collect data")

    return parser.parse_args()

def connect_to_sercom(port, retry_timeout_s):
    """connect to serial device, if fail, retry within given timeout."""
    start_time = int(time.time())
    while(int(time.time() - start_time) < retry_timeout_s):
        try:
            ser = serial.Serial(port, 19200, timeout=1)
            if(ser.is_open == True):
                break
        except:
            pass

    return ser

if __name__ == '__main__':
    args = get_args()
    ser = connect_to_sercom(args.comport, 30)

    if(ser.is_open == False):
        print "Cannot open port"
        sys.exit(1)
    else:
        print "Connected to serial com device ",args.comport

    start_time = int(time.time()) # in seconds
    while((int(time.time()) - start_time) < args.duration):
        line = ser.readline()

        if(line != ''):
            print line.strip()

        for key in list(matched_str_cnt):
            if(line.find(key) >= 0):
                    matched_str_cnt[key] +=1

    ser.close()

    # Summary
    print "\n=== Statiscal Summary duration ", args.duration,"(s) ==="
    print "count: event"
    for key in sorted(matched_str_cnt.iterkeys()):
        print matched_str_cnt[key], ": ",key

