#!/bin/env bash

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
    if [ ! -d "$TOOLCHAINS_PATH" ] ; then
        echo " $TOOLCHAINS_PATH not found!"
        echo "Install Particle Workbench Toolchains from https://www.particle.io/workbench/"
        exit 1;
    fi

    # Ensure Particle CLI has been instaled
    if ! type -P particle ; then
        echo "Particle CLI not detected, install it by:"
        echo "bash <( curl -sL https://particle.io/install-cli )"
        echo "and add to PATH"
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
    export PLATFORM=argon
}

print_usage() {
    echo "Usage:"
    echo -e "\t ./build.sh -h                               Display help."
    echo -e "\t ./build.sh -c [all/app] -l [usb/cloud] -v   Clean and build with given option, optional verbose"
    echo -e "\n"
}

clean_bin() {
    # Clean
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
            # do nothing, user does not want to clean
            ;;
    esac

    clean_error=$?
    if [ "$clean_error" -gt 0 ] ; then
        exit $clean_error
    fi
}

build_bin() {
    # Build
    make compile-all v="$verbose_level"

    build_error=$?
    if [ "$build_error" -gt 0 ] ; then
        exit $build_error
    fi
}

load_bin() {
    case $load_opt in
        usb)
            echo "loading binary via usb"
            particle usb dfu
            particle flash --usb ./target/argon/*.bin
            ;;
        cloud)
            echo " Loading via cloud Not supported yet!"
            exit 1
            ;;
        *)
            exit 0 #user doesn't want to load
            ;;
    esac

}

### Entry ###
check_env
setup_env

# default options
clean_opt=""
load_opt=""
verbose_level=0 # silent by default

# Anything inside "::" are valid options.
while getopts ":h:v:c:l:" opt; do
    case ${opt} in
        h)
            print_usage
            exit 0
            ;;
        c)
            clean_opt=$OPTARG
            echo "clean $clean_opt"
            ;;
        l)
            load_opt=$OPTARG
            echo "load $load_opt"
            ;;
        :)
            case $OPTARG in
                v)
                    verbose_level=1
                    echo "verbose $verbose_level"
                    ;;
                *)
                    echo "Invalid option: $OPTARG" 1>&2
                    print_usage
                    exit 1
            esac
            ;;

        \?)
            echo "Invalid Option: -$OPTARG" 1>&2
            print_usage
            exit 1
            ;;
    esac
done

clean_bin
build_bin
load_bin
