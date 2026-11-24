#ifndef __SWEEPING_TASK__
#define __SWEEPING_TASK__

#include "kernel/Task.h"
#include "devices/ServoMotor.h"
#include "devices/Pot.h"
#include "devices/Sonar.h"
#include "devices/LCDScreen.h"
#include "model/Context.h"
#include <Arduino.h>

#define D1 2
#define D2 1
class SweepingTask: public Task {

public:
  SweepingTask(
     ServoMotor* servo,
     Sonar* sonar,
     LCDScreen* screen,
     Potentiometer* pot,
     Context* pContext); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  bool checkAndSetJustEntered();
  float readSonarWriteLCD();

  enum { IDLE, STARTING, AUTOMATIC, MANUAL };
  int state;
  long stateTimestamp;
  bool justEntered;
  ServoMotor* servoMotor;
  Sonar* sonar;
  LCDScreen* screen;
  Potentiometer* pot;
  Context* context;
  int currentPos;
  bool toBeStopped;
};

#endif