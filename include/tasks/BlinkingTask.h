#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/Led.h"
#include <Arduino.h>

class BlinkingTask: public Task {

public:
  BlinkingTask(Led* pLed, Context* pContext); 
  virtual void tick() = 0;

protected:
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  bool checkAndSetJustEntered();
  
  enum { IDLE, ON, OFF};
  int state;
  long stateTimestamp;
  bool justEntered;

  Led* pLed;
  Context* pContext;
};

#endif