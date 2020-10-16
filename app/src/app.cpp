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

    temp = dht.getTempFarenheit();
    humidity = dht.getHumidity();

    Serial.printlnf("Temp: %f", temp);
    Serial.printlnf("Humidity: %f", humidity);

    delay(10000);delay(2000); 
}
