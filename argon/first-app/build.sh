#!/bin/bash

export PARTICLE_CLI_PATH=$HOME/bin/particle
export APPDIR=$PWD
export DEVICE_OS_PATH=$HOME/.particle/toolchains/deviceOS/1.5.0
export PLATFORM=argon
#export PLATFORM_ID=  # no need, the platform deduce this from $PLATFORM

make compile-all
