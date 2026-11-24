#include "devices/LCDScreen.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LCDScreen::LCDScreen(): screen(0x27, 20, 4) {
    screen.init();
    this->screen.backlight();
}

void LCDScreen::print(const String msg) {
    this->clear();
    this->screen.setCursor(0,0);
    this->screen.print(msg);
}

void LCDScreen::clear() {    
    this->screen.clear();
}


