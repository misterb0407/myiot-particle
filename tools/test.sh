#!/bin/bash

export url=https://api.particle.io/v1/devices
export id=e00fce688db39b9f6bcd0149
export token=$1
export query=$2

curl "$url/$id/$query?access_token=$token"
