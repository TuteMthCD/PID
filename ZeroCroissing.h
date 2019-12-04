#include "Arduino.h"

class ZeroCroissing {
private:
static unsigned char outPin;
public:
static unsigned int pinUP;      //de 0 a 9999 que nos encontramos en una señal de 50Hz

void begin(unsigned char,unsigned char);
static unsigned char Change;
static void ZeroCroissing_Interrupt(void);
};
