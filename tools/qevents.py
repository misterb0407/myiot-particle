#!/usr/bin/env python3

"""Script to query stream events of particular given device from Particle Cloud.

To install sseclient:
    pip3 install sseclient
"""
import argparse
import sys
import time
import json
import base64
import threading
from sseclient import SSEClient

lock = threading.Lock()

# dictionary of device name to device id
DEVID = {
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

EVENTS_CNT = {
    'v1-observation-values':0,
    'v1-observation-settings':0,
    'v1-device-meta':0,
    'v1-patient-meta':0,
    }

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

def decode(data):
    """To decode base64 encoded data."""
    decoded_data = base64.b64decode(data)
    # still can understand the data
    # ref: you can checkout the method in DecodeV1ObservationValues
    # in MessageDecoder.cs
    return decoded_data

def is_found(devicename):
    """To search if given device found in the valid device names list."""
    for dev in list(DEVID):
        if dev == devicename:
            return True
    return False

def print_valid_devices():
    """Tell user which devices are supported."""
    print("valid device names")
    for dev in list(DEVID):
        print(dev)

def get_stream(event_name):
    """To get the stream events object."""
    url = "https://api.particle.io/v1/events/"+event_name
    headers = {'Authorization': 'Bearer '+args.token}
    start_time = int(time.time())

    events = SSEClient(url, headers=headers)
    for curr_event in events:
        if curr_event.data.count('data') > 0:
            coreid = json.loads(curr_event.data)['coreid']
            if coreid.strip() == DEVID[args.devname].strip():
                lock.acquire()
                EVENTS_CNT[event_name] += 1
                lock.release()
                data_base64 = json.loads(curr_event.data)['data']
                decode(data_base64)
                print("%s\n%s\n%s\n" %(event_name, curr_event, decode(data_base64)))

        if(int(time.time()) - start_time) > args.duration:
            break

if __name__ == '__main__':
    args = get_args()

    if is_found(args.devname) is False:
        print("device not found!")
        print_valid_devices()
        sys.exit(1)

    threads = []

    for event in list(EVENTS_CNT):
        threads.append(threading.Thread(target=get_stream, args=(event,)))

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

    # Summary
    print("count: event name")
    for event in list(EVENTS_CNT):
        print("%d: %s" %(EVENTS_CNT[event], event))
