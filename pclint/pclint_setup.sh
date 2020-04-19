#!/bin/bash

export LINT_FILE=co-gcc.lnt
export LINT_HEADER=co-gcc.h

$HOME/tools/pclp-1.3-linux-eval2/linux/config/pclp_config.py \
    --compiler=gcc \
    --compiler-bin=$HOME/.particle/toolchains/gcc-arm/5.3.1/bin/arm-none-eabi-gcc \
    --config-output-lnt-file=$LINT_FILE \
    --config-output-header-file=$LINT_HEADER \
    --generate-compiler-config

if [ -f ./$LINT_FILE ] ; then
    $HOME/tools/pclp-1.3-linux-eval2/linux/pclp64_linux_debug $LINT_FILE ../app/src/*.cpp
fi

