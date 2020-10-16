#include "Grove_Temperature_And_Humidity_Sensor.h"
#include "Grove_ChainableLED.h"

#include "platform.h"

DHT dht(D2); // temperature and humidity sensor
ChainableLED leds(A4, A5, 1); // Chainable LED

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

void setup() {
    API.init();
    System.on(all_events, &eventHandler);
    dht.begin();
    leds.init();
    leds.setColorHSB(0, 0.0, 0.0, 0.0);
}


void loop() {
    float temp, humidity;

    temp = dht.getTempCelcius();
    humidity = dht.getHumidity();

    Serial.printlnf("Temp: %0.2f C", temp);
    Serial.printlnf("Humidity: %0.2f", humidity);

    toggleLed("");
    delay(2000);
}
