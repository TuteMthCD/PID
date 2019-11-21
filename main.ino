#include "SpinWheel.h"
#include "ZeroCroissing.h"
#include <PID_v1.h>

#define PD2 2   //pata en arduino llamada "2"
#define PD3 3   //pata en arduino llamada "3"
#define PD5 5  //pata en arduino llamada "5"

//varaibles de clases
SpinWheel Encoder;
ZeroCroissing Detector;

//varibles de para el uso de la libreria PID
double Setpoint, Input, Output;
double Kp=2, Ki=0.0125, Kd=10;

PID PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup(){
        //incio de objetos/clases
        Serial.begin(115200);
        Encoder.begin(PD2);
        Detector.begin(PD3,PD5);

        //configuraciones del PID
        PID.SetSampleTime(250);     //calcula cada 250ms
        PID.SetOutputLimits(0,2499); //valores de 0 a 2500 min and max , por 25 ms cada ciclo
        PID.SetMode(MANUAL);        //significa que yo llamo a que calcule, por lo tanto SetSampleTime queda "inhabilitado"
}

void loop() {
        Setpoint=100;
        Input=Encoder.RPM;

        if(Detector.Change) {
                PID.Compute();
                Detector.Change=0;
        }

        Detector.pinUP=Output;
        Detector.loop();
}
