#include "Grove_Temperature_And_Humidity_Sensor.h"

#include "platform.h"

DHT dht(D2);

void eventHandler(system_event_t event, int param) {
    uint32_t lsb_event = static_cast<uint32_t>(event);
    Log.info("evt 0x%08lX param 0x%X", lsb_event, param);
}

void setup() {
    API.init();
    System.on(all_events, &eventHandler);
    dht.begin();
}


void loop() {
    float temp, humidity;

    temp = dht.getTempCelcius();
    humidity = dht.getHumidity();

    Serial.printlnf("Temp: %0.2f C", temp);
    Serial.printlnf("Humidity: %0.2f", humidity);

    delay(2000);
}
