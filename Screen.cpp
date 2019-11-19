#include "Screen.h"

#define PC0 A0
#define PC1 A1
#define PC2 A2
#define PC3 A3
#define PC4 A4
#define PC5 A5

LiquidCrystal lcd(PC0, PC1, PC2, PC3, PC4, PC5);

#define Flecha 0
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

void lcd_init(void){
        lcd.begin(16,2);
        lcd.noCursor()
        lcd.noBlink()
        //lcd.noAutoscroll();
        //lcd.leftToRight();
        lcd.clear();
        lcd.createChar(Flecha, flechaChar);
        lcd.home();
        lcd.display();
}

void lcd_showRPM(double rmp){
  
}
