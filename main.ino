#include "SpinWheel.h"
#include "ZeroCroissing.h"
#include "Screen.h"
#include <PID_v1.h>

#define PD2 2   //pata en arduino llamada "2"
#define PD3 3   //pata en arduino llamada "3"
#define PD5 5  //pata en arduino llamada "5"

//varaibles de clases
SpinWheel Encoder;
ZeroCroissing Detector;

//varibles de para el uso de la libreria PID
double Setpoint, Input, Output;
double Kp=1, Ki=0.0015, Kd=3;


PID PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

void setup(){
        //incio de objetos/clases
        //Serial.begin(115200);
        Encoder.begin(PD2);
        Detector.begin(PD3,PD5);

        viaco_vars(&Input,&(Encoder.RPM), &Setpoint, &Kp, &Ki, &Kd);
        init_viaco();

        //configuraciones del PID
        PID.SetSampleTime(20);     //calcula cada 250ms
        PID.SetOutputLimits(0,11000); //valores de 0 a ___ min and max , por 10 ms cada ciclo
        PID.SetMode(AUTOMATIC);    //significa que yo llamo a que calcule, por lo tanto SetSampleTime queda "inhabilitado"

        Detector.pinUP=10;
        Setpoint=1000;

}

void loop() {
        if(PID.Compute()) {
                if(Detector.Change) {
                        Input=Encoder.RPM;
                        if(Output) {
                                Detector.pinUP=Output;
                        }
                        PID.SetTunings(Kp, Ki, Kd);
                }
        }
        viaco_loop();
}
