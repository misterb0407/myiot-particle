#!/bin/bash

#### Description: A wrapper build script on top of Particle Workbench Platform.
#### It is assumed the Workbench platform and tool chain has been installed in
#### ~/.particle path. If not, install it from
#### https://www.particle.io/workbench/.
#### Author: Parhusip, Babang Putra
#### Date: 04-Apr-2020


export PARTICLE_CLI_PATH=$HOME/bin/particle
export APPDIR=$PWD
export DEVICE_OS_PATH=../device-os
export PLATFORM=argon
#export PLATFORM_ID=  # no need, the Workbench platform deduce this from $PLATFORM

#TODO : to implement check whether particle workbench and cli has been installed

print_usage() {
    echo "Usage:"
    echo -e "\t ./build.sh -h         Display help."
    echo -e "\t ./build.sh -c all     Clean both devos and app fw."
    echo -e "\t ./build.sh -c app     Clean app fw only excluding devos fw."
    echo -e "\n"
}

# if no argument, by default just compile the change only, no clean
if [[ $# -eq 0 ]]; then
    make compile-all
    exit 0
fi

# Anything inside "::" are valid options
while getopts ":hc:" opt; do
    case ${opt} in
        h )
            print_usage
            exit 0
            ;;
        c)
            clean_opt=$OPTARG
            ;;
        :)
            echo "Invalid option: $OPTARG" 1>&2
            print_usage
            exit 1
            ;;
        \? )
            echo "Invalid Option: -$OPTARG" 1>&2
            print_usage
            exit 1
            ;;
    esac
done

case $clean_opt in
    all)
        echo "clean both devos fw and app fw"
        make clean-all
        ;;
    app)
        echo "clean app fw"
        make clean-user
        ;;
    *)
       echo "unknown -c argument" "$clean_opt"
        print_usage
        exit 1
        ;;
esac

make compile-all
