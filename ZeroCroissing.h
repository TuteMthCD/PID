#include "Arduino.h"

class ZeroCroissing {
private:
static unsigned long before;
static unsigned char outPin;
public:
unsigned int pinUP;      //de 0 a 2500 que nos encontramos en una señal de 50Hz

void begin(unsigned char,unsigned char);
void loop(void);

static unsigned char Change;
static void ZeroCroissing_Interrupt(void);
};
