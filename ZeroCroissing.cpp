#include "ZeroCroissing.h"

unsigned char ZeroCroissing::outPin=0;
unsigned long ZeroCroissing::before=0;

unsigned char ZeroCroissing::Change=0;

void ZeroCroissing::begin(unsigned char inputPin, unsigned char pinSalida){
        outPin=pinSalida;
        pinMode(inputPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(inputPin), ZeroCroissing_Interrupt,LOW);
        //Serial.print("Iniciada interrupcion de la pata " + inputPin);
        //Serial.print("Cruce por 0");
}

void ZeroCroissing::ZeroCroissing_Interrupt(void){
        before = micros();
        __asm__ ("nop\n\t"); //pierdo un pulso de clock
        digitalWrite(outPin,LOW);
        Change=1;
}

void ZeroCroissing::loop(void){
        if((micros()-before) >= pinUP) digitalWrite(outPin,HIGH);
}
