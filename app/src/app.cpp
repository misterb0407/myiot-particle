#include "platform.h"

class App {
    public:
        App(){}
        static int32_t echo(String input) {
            Log.info(input);
            return 0;
        }
};


void setup() {
    API.init();
    Particle.function("echo", App::echo);

}

void loop() {
    delay(2000);
}
