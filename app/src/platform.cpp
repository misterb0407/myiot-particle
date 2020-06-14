#include "platform.h"

using namespace platform;

const Platform& API = Platform::getInstance();

/**
 * As per device OS documentation, applicationn still need
 * to instatiate following Log handler object to use serial
 * over USB interface. Only then application can use library
 * object Log to generate logging while the handler acts as
 * sinks for overall logging both from system and application.
 * ref: https://docs.particle.io/reference/device-os/firmware/argon/#logging
 */

SerialLogHandler logHandler(LOG_LEVEL_WARN, {
    { "app", LOG_LEVEL_INFO },
    { "app.network", LOG_LEVEL_TRACE }
});

Platform& Platform::getInstance() {
    static Platform Instance;

    return Instance;
}

void Platform::init() {
}

void Platform::regCloudFunc(platform::CloudFunc* fns, uint32_t count) {
    if (fns == nullptr) {
        return;
    }

    for(auto i = 0U; i < count; i++) {
        Particle.function(fns->name, fns->fn);
        fns++;
    }
}

