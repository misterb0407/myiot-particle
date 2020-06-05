#include "platform.h"

bool flag = false;
int analogvalue = 0;
double tempC = 0;
String message = "my name is Babang Putra";
String aString;


void setup() {
    API.init();
    Particle.variable("flag", flag);
    Particle.variable("analogvalue", analogvalue);
    Particle.variable("temp", tempC);
    if(Particle.variable("mess", message) == false)
    {
        //variable not registered!
    }
    Particle.variable("mess2", aString);

    pinMode(A0, INPUT);

}

void loop() {
    //Read the analog value of the sensor TMP36
    analogvalue = analogRead(A0);
    //convert the reading into degree Celcius
    tempC = (((analogvalue * 3.3) / 4095) - 0.5) *100;
    Log.info("testing %lf", tempC);
    delay(2000);
}
