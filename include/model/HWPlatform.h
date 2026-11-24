#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "devices/Button.h"
#include "devices/Led.h"
#include "devices/Sonar.h"
#include "devices/LCDScreen.h"
#include "devices/ServoMotor.h"
#include "devices/Pot.h"
#include "devices/TempSensorLM35.h"

class HWPlatform {

public:
  HWPlatform();
  void init();
  void test();

  Button* getButtonStart();
  Button* getButtonReset();
  Button* getButtonStop();
  Sonar* getSonarSensor();
  
  Led*  getRedLed();
  Led* getGreenLed();
  LCDScreen* getLCDScreen();
  ServoMotor* getMotor();
  Potentiometer* getPot();

private:
  Button* startButton;
  Button* resetButton;
  Button* stopButton;
  Led* greenLed;
  Led* redLed;
  ServoMotor* servoMotor;
  Sonar* sonar;
  LCDScreen* screen;
  TempSensorLM35* temp; 
  Potentiometer* pot;
  
};

#endif
