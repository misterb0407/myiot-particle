#!/bin/bash

# (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
# SW guideline: Technote Coding Guidelines Ver. 1.6 

#### Description: A wrapper build script on top of Particle Workbench Platform.
#### It is assumed the Workbench platform and tool chain has been installed in
#### ~/.particle path. If not, install it from
#### https://www.particle.io/workbench/.
#### Author: Parhusip, Babang Putra
#### Date: 04-Apr-2020

export TOOLCHAINS_PATH=$HOME/.particle/toolchains

# To ensure toolchains installed
check_env() {
    # Ensure Particle Workbench has been installed
    if [ ! -d $TOOLCHAINS_PATH ] ; then
        echo " $TOOLCHAINS_PATH not found!"
        echo "Install Particle Workbench Toolchains from https://www.particle.io/workbench/"
        exit 1;
    fi

    # Ensure Particle CLI has been instaled
    if [ ! -x $HOME/bin/particle ] ; then
        echo "Particle CLI not detected, install it by:"
        echo "bash <( curl -sL https://particle.io/install-cli )"
        exit 1;
    fi
}

# To setup build environment
setup_env() {
    export PATH=$TOOLCHAINS_PATH/gcc-arm/5.3.1/bin:$PATH # for ARM GCC compiler
    export PATH=$TOOLCHAINS_PATH/buildtools/1.1.1:$PATH # for cmake etc

    # For particle build environment
    export PARTICLE_CLI_PATH=$HOME/bin/particle
    export APPDIR=$PWD
    export DEVICE_OS_PATH=$TOOLCHAINS_PATH/deviceOS/1.5.0
    export PLATFORM=electron
}

print_usage() {
    echo "Usage:"
    echo -e "\t ./build.sh -h         Display help."
    echo -e "\t ./build.sh -c all     Clean both devos and app fw."
    echo -e "\t ./build.sh -c app     Clean app fw only excluding devos fw."
    echo -e "\n"
}

check_env
setup_env

# if no argument, by default just rebuild with change in app code only. In
# Bernina Device, most of the time, we should not need to touch device OS fw.
if [[ $# -eq 0 ]]; then
    make compile-user
    exit 0
fi

# Anything inside "::" are valid options.
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
