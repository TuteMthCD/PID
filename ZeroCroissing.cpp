#include "ZeroCroissing.h"

#define pre_8 (0 << CS12)|(1 << CS11)|(0 << CS10)
#define pre_off (0 << CS12)|(0 << CS11)|(0 << CS10)

void init_timer1(void);

unsigned char ZeroCroissing::outPin=0;

unsigned char ZeroCroissing::Change=0;

void ZeroCroissing::begin(unsigned char inputPin, unsigned char pinSalida){
        pinMode(inputPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(inputPin), ZeroCroissing_Interrupt,FALLING);
        outPin=pinSalida;
        pinMode(outPin, OUTPUT);

        //Serial.print("Iniciada interrupcion de la pata " + inputPin);
        //Serial.print("Cruce por 0");
        init_timer1();
}

static unsigned int ZeroCroissing::pinUP=0;

void ZeroCroissing::ZeroCroissing_Interrupt(void){
        PORTD = (0<<PD5);
        OCR1A=pinUP;
        TCNT1 = 0;// Incio el contador en 0
        TCCR1B |= pre_8;// pre-esclaer en 64
        Change=1;
}

ISR(TIMER1_COMPA_vect) {
        TCCR1B |= pre_off;
        asm ("nop");
        PORTD = (1<<PD5);
}

void init_timer1(void){
        noInterrupts();
        TCCR1A = 0; // El registro de control A queda todo en 0
        TCCR1B = 0; // activo el modo CTC en Timer1
        TCCR1B |= (1 << WGM12);

        TCNT1 = 0;// Incio el contador en 0

        OCR1A = 10000;// El registro comparador 50K (este debo modificar para lanzar la interrupcion "salida PID")

        TCCR1B |=pre_off;

        TIMSK1 |= (1 << OCIE1A);// Inicializamos el comparador para el registro A

        interrupts();// Activamos interrupciones nuevamente
}
