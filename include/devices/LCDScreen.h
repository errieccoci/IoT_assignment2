#ifndef __LCDSCREEN__
#define __LCDSCREEN__

#include <LiquidCrystal_I2C.h>

class LCDScreen {
    public:
        LCDScreen();
        void print(const String msg);
        void clear();
    private:
        LiquidCrystal_I2C screen;
};

#endif