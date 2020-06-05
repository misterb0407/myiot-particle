#include "platform.h"

const Platform& API = Platform::getInstance();

/**
 * As per device OS documentation, applicationn still need
 * to instatiate following Log handler object to use serial
 * over USB interface. Only then application can use library
 * object Log to generate logging while the handler acts as
 * sinks for overall logging both from system and application.
 * ref: https://docs.particle.io/reference/device-os/firmware/argon/#logging
 */
SerialLogHandler logHandler;

Platform& Platform::getInstance() {
    static Platform Instance;

    return Instance;
}

void Platform::init() {
}

