#include "platform.h"

void eventHandler(system_event_t event, int param) {
    uint32_t lsb_event = static_cast<uint32_t>(event);
    Log.info("evt 0x%08lX param 0x%X", lsb_event, param);
}

void setup() {
    API.init();
    System.on(all_events, &eventHandler);
}


void loop() { delay(2000); }
