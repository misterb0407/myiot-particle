#include "platform.h"

Platform& Platform::getInstance() {
    static Platform Instance;

    return Instance;
}

