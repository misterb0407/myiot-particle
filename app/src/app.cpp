#include <cmath>

#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "Grove_ChainableLED.h"
#include "PublishQueueAsyncRK.h"

#include "platform.h"

DHT dht(D2); // temperature and humidity sensor
ChainableLED leds(A4, A5, 1); // Chainable LED
double currentLightLevel = 0;
double prevLightLevel = currentLightLevel;
double g_LightTreshold = 50;

double currentHumidity = 0;
double prevHumidity = currentHumidity;

double currentTemp = 0;
double prevTemp = 0;

retained uint8_t publishQueueRetainedBuffer[2048];
PublishQueueAsync publishQueue(publishQueueRetainedBuffer, sizeof(publishQueueRetainedBuffer));

void eventHandler(system_event_t event, int param) {
    uint32_t lsb_event = static_cast<uint32_t>(event);
    Log.info("evt 0x%08lX param 0x%X", lsb_event, param);
}

int toggleLed(String args) {
    leds.setColorHSB(0, 0.0, 1.0, 0.5);// turn red
    delay(500);
    leds.setColorHSB(0, 0.0, 0.0, 0.0);// turn off
    delay(500);

    return 1;
}

int setLightTreshold(String args) {
    g_LightTreshold = args.toFloat();

    return g_LightTreshold;
}

void setup() {
    API.init();
    System.on(all_events, &eventHandler);
    dht.begin();
    leds.init();
    leds.setColorHSB(0, 0.0, 0.0, 0.0);
    pinMode(A0, INPUT);// light sensor as input

    //  Cloud functions
    Particle.function("light treshold", setLightTreshold);
}


void loop() {
    currentTemp = dht.getTempCelcius();
    currentHumidity = dht.getHumidity();
    double lightAnalogVal = analogRead(A0);
    currentLightLevel = map(lightAnalogVal, 0.0, 4095.0, 0.0, 100.0);

    if ((currentTemp - prevTemp > 2) || (currentTemp < prevTemp - 2)) {
        Serial.printlnf("Temp: %0.2f C", currentTemp);
        publishQueue.publish("temperature/level",
        String(currentTemp), PRIVATE);
        delay(1000);
    }

    if ((currentHumidity - prevHumidity >= 5) || (currentHumidity <= prevHumidity - 5)) {
        Serial.printlnf("Humidity: %0.2f", currentHumidity);
#if(0)
        publishQueue.publish("humidity/level",
        String(currentHumidity), PRIVATE);
#endif
        delay(1000);
    }


    //toggleLed("");

    if ((currentLightLevel > (prevLightLevel + 5)) || (currentLightLevel < (prevLightLevel - 5))) {
        Serial.printlnf("light level: %0.2f", currentLightLevel);
        publishQueue.publish("light-meter/level",
        String(currentLightLevel), PRIVATE);
        delay(1000);
    }

    prevTemp = currentTemp;
    prevHumidity = currentHumidity;
    prevLightLevel = currentLightLevel;

    delay(2000);//important for the reading reability

}
