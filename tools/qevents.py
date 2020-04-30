#!/usr/bin/env python3

"""Script to query stream events of particular given device from Particle Cloud.

To install sseclient:
    pip3 install sseclient
"""
import requests
import argparse
import sys
import time
import json
import base64

from sseclient import SSEClient

# dictionary of device name to device id
devid = {
        'electron-0009': '430061000451353431383736',
        'electron-0011': '330031000d47373336373936',
        'electron-0017': '1f0035000b47373336373936',
        'electron-0020': '28001f000747373334363431',
        'electron-0016': '300026000247373334363431',
        'electron-0014': '1f002e000647373336373936',
        'electron-0015': '39002b000e47373334363431',
        'electron-0012': '230038000f47373334363431',
        'electron-0019': '4a003f001750483553353920',
        'electron-0013': '230029000147373336373936',
        }

events_cnt = {
        'v1-observation-values':0,
        'v1-observation-settings':0,
        'v1-device-meta':0,
        'v1-patient-meta':0,
        }
decoded_data=""

def get_args():
    """Parse the input argument."""
    parser = argparse.ArgumentParser()

    parser.add_argument("-n", "--devname", required=True,
           help="device name e.g. electron-0009")
    parser.add_argument("-d", "--duration", required=True,
           type=int, help="duration in secs to collect data")
    parser.add_argument("-t", "--token", required=True,
           help="token for GET http request")

    return parser.parse_args()

def decode(event):
    """To decode base64 encoded data."""
    # extract
    data_base64 = json.loads(event.data)['data']
    coreid = json.loads(event.data)['coreid']
    # TODO to decode base64 data
    print(event)
    global decoded_data
    decoded_data = base64.b64decode(data_base64)
    # still can understand the data
    # ref: you can checkout the method in DecodeV1ObservationValues
    # in MessageDecoder.cs
    sys.exit(1)
    print(base64.b64decode(data_base64))

def is_found(devicename):
    """To search if given device found in the valid device names list."""
    for dev in list(devid):
        if (dev == devicename):
            return True

    return False

def print_valid_devices():
    """Tell user which devices are supported."""
    print("valid device names")
    for dev in list(devid):
        print(dev)

def get_stream(event):
    """To get the stream events object."""
    url =  "https://api.particle.io/v1/events/"+event
    headers = {'Authorization': 'Bearer '+args.token}
    return SSEClient(url, headers = headers)

if __name__ == '__main__':
    args = get_args()

    if is_found(args.devname) == False :
        print("device not found!")
        print_valid_devices()
        sys.exit(1)

    # TODO: to query for all events, for now just one
    # Maybe can leverage python multi threading feature?
    event_type = 'v1-observation-values'
    events = get_stream(event_type)

    start_time = int(time.time())
    for event in events:
        if event.data.count('data') > 0:
            coreid = json.loads(event.data)['coreid']
            if coreid.strip() == devid[args.devname].strip():
                events_cnt[event_type] +=1
                decode(event)

        if((int(time.time()) - start_time) > args.duration):
            break


    # Summary
    print("count: event name")
    for event in list(events_cnt):
        print("%d: %s" %(events_cnt[event], event))

