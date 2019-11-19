#include "SpinWheel.h"

#define PD2 2   //pata en arduino llamada "2"

SpinWheel Encoder;

void setup(){
        Serial.begin(19200);
        Encoder.begin(PD2);
}

void loop() {
        Serial.println(int(Encoder.RPM));
}
