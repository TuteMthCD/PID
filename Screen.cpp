#include "Screen.h"

#define PC0 A0
#define PC1 A1
#define PC2 A2
#define PC3 A3
#define PC4 A4
#define PC5 A5

#define pinA 6
#define pinB 7
#define pinSW 8

LiquidCrystal lcd(PC0, PC1, PC2, PC3, PC4, PC5);

#define Flecha (char)0
byte flechaChar[] = {
        B00000,
        B01000,
        B01100,
        B01110,
        B01110,
        B01100,
        B01000,
        B00000
};

struct {
        String palabra;
        double *numero;
} lcdContenido[6];

void viaco_vars(double *pInput,double *pRPM,double *pSetpoint,double *pKp,double *pKi, double *pKd){
        lcdContenido[0].palabra="PID Velocidad";
        //  lcdContenido[0].numero=nose;
        lcdContenido[1].palabra="RPM";
        lcdContenido[1].numero=pRPM;
        lcdContenido[2].palabra="Setpoint";
        lcdContenido[2].numero=pSetpoint;
        lcdContenido[3].palabra="Kp";
        lcdContenido[3].numero=pKp;
        lcdContenido[4].palabra="Ki";
        lcdContenido[4].numero=pKi;
        lcdContenido[5].palabra="Kd";
        lcdContenido[5].numero=pKd;
}


void init_viaco(void){
        pinMode(pinA,INPUT);
        pinMode(pinB,INPUT);
        pinMode(pinSW,INPUT);

        lcd.begin(16,2);
        lcd.noCursor();
        lcd.noBlink();
        //lcd.noAutoscroll();
        //lcd.leftToRight();
        lcd.clear();
        lcd.createChar(Flecha, flechaChar);
        lcd.home();
        lcd.display();
        //lcd.write(Flecha);

        lcd.print(lcdContenido[0].palabra);
}

void viaco_loop(void){
        char A = digitalRead(pinA);
        char B = digitalRead(pinB);
        char SW= digitalRead(pinSW);

        static bool editmode=0;
        static char cifra=0;
        bool printLCD=0;

        static char lastA=HIGH;
        static char lastSW=HIGH;
        static int num=0;

        if(SW==HIGH && lastSW==LOW) {
                if(num==0 || num==1) num=2;
                //if(!(num==1))
                if(editmode) {
                        if(cifra<3) {
                                cifra++;
                        }else{
                                cifra=0;
                                editmode=0;
                        }
                }else editmode=1;
                //editmode=~editmode;
                printLCD=1;
        }
        if(A==HIGH && lastA==LOW) {
                if (B==HIGH) {
                        if(editmode) {
                                switch (cifra) {
                                case 0:
                                        (*lcdContenido[num].numero)-=1;
                                        break;
                                case 1:
                                        (*lcdContenido[num].numero)-=10;
                                        break;
                                case 2:
                                        (*lcdContenido[num].numero)-=100;
                                        break;
                                case 3:
                                        (*lcdContenido[num].numero)-=1000;
                                        break;
                                }
                        }else if(num) num--;
                }else if(editmode) {
                        switch (cifra) {
                        case 0:
                                (*lcdContenido[num].numero)+=1;
                                break;
                        case 1:
                                (*lcdContenido[num].numero)+=10;
                                break;
                        case 2:
                                (*lcdContenido[num].numero)+=100;
                                break;
                        case 3:
                                (*lcdContenido[num].numero)+=1000;
                                break;
                        }
                }else if(num<5) num++;
                printLCD=1;
        }

        if(num==1) {
                static long before=0;
                long time=millis();
                if(before < time) {
                        printLCD=1;
                        before = millis()+1000;
                }
        }

        if(printLCD) {
                lcd.clear();
                lcd.print(lcdContenido[num].palabra);
                if(!(num==0)) {
                        lcd.setCursor(6,1);
                        lcd.print((int)*(lcdContenido[num].numero));
                }
        }
        if(editmode) {
                switch (cifra) {
                case 0:
                        lcd.setCursor(14,0);
                        lcd.print("x1");
                        break;
                case 1:
                        lcd.setCursor(13,0);
                        lcd.print("x10");
                        break;
                case 2:
                        lcd.setCursor(12,0);
                        lcd.print("x100");
                        break;
                case 3:
                        lcd.setCursor(11,0);
                        lcd.print("x1000");
                        break;
                default:
                        cifra=0;
                }
                lcd.setCursor(0,1);
                lcd.write(Flecha);
        }
        lastA=A;
        lastSW=SW;
}
