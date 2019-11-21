#include "SpinWheel.h"

void SpinWheel::begin(unsigned char inputPin){
        pinMode(inputPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(inputPin), SpinWheel_Interrupt,LOW);
        //Serial.print("Iniciada interrupcion de la pata " + inputPin);
        //Serial.print("Cruce por 0");
}

static double SpinWheel::RPM=0;

void SpinWheel::SpinWheel_Interrupt(void){
        static unsigned long before=0;
        RPM =(1/(micros()-before)*12)*60; //rpm Interrupcion
        before = micros();
}
