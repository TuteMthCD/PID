#include "Arduino.h"

class ZeroCroissing {
private:
static unsigned long before;
static unsigned char outPin;
public:
unsigned int pinUP;      //de 0 a 2500 que nos encontramos en una señal de 50Hz
static unsigned char Change;

void begin(unsigned char,unsigned char);
void loop(void);

static void ZeroCroissing_Interrupt(void);
};
