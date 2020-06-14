#include "platform.h"

int32_t getTime(String input) {
    Log.info("%ld", Time.now());

    return 0;
}

int32_t getMillis(String input) {
    Log.info("%lu", millis());

    return 0;
}

int32_t getMicros(String input) {
    Log.info("%lu", micros());

    return 0;
}


platform::CloudFunc gCloudFunc[] = {
    {"time", &getTime},
    {"time(ms)", &getMillis},
    {"time(us)", &getMicros}
};


void setup() {
    API.init();
    API.regCloudFunc(gCloudFunc, sizeof(gCloudFunc)/sizeof(gCloudFunc[0]));

}

void loop() {
    delay(2000);
}
