#!/usr/bin/env python3

import requests

url = 'https://api.particle.io/v1/devices'
id = 'e00fce688db39b9f6bcd0149'
token = '12a408868eac3e35d7c4a88f42b3d5735a2d71e13534'
query = 'mess'

r = requests.get(url+'/'+id+'/'+query+'?access_token='+token)

print("req status:", r.status_code)

response_dict = r.json()
print(response_dict)


