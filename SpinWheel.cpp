#include "SpinWheel.h"

void SpinWheel::begin(unsigned char inputPin){
        pinMode(13,OUTPUT);
        pinMode(inputPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(inputPin), SpinWheel_Interrupt,FALLING);
        //Serial.print("Iniciada interrupcion de la pata " + inputPin);
}

static double SpinWheel::RPM=0;

void SpinWheel::SpinWheel_Interrupt(void){
        static unsigned long before;
        unsigned long time=micros();
        RPM=2500000/((time-before)); //rpm Interrupcion
        //RPM=time-before;
        before = time;
}
