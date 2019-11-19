#include "Arduino.h"

class SpinWheel {
private:
public:
  static double RPM;

  void begin(unsigned char);

  static void SpinWheel_Interrupt(void);
};
