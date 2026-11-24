#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "model/HWPlatform.h"
#include "tasks/TestHWTask.h"
#include "tasks/SweepingTask.h"
#include "tasks/BlinkingTask.h"
#include "tasks/BlinkingGreenTask.h"
#include "tasks/ButtonTask.h"
#include "tasks/BlinkingRedTask.h"

// #define __TESTING_HW__

Scheduler sched;
HWPlatform* pHWPlatform;
// Context rappresenta il contesto, 
// ossia se c'è qualcuno che sta usando le risorse oppure no
Context* pContext;

void setup() {
  MsgService.init();
  sched.init(50);

  Logger.log(":::::: Sweeping System ::::::");
  
  pHWPlatform = new HWPlatform();
  pHWPlatform->init();

#ifndef __TESTING_HW__
  pContext = new Context();

  Task* pBlinkingGreen = new BlinkingGreenTask(pHWPlatform->getGreenLed(), pContext);
  pBlinkingGreen->init(200);
  Task* pBlinkingRed = new BlinkingRedTask(pHWPlatform->getRedLed(), pContext);
  pBlinkingRed->init(200);
  Task* pButton = new ButtonTask(
    (ButtonImpl*)pHWPlatform->getButtonStart(), 
    (ButtonImpl*)pHWPlatform->getButtonStop(), 
    (ButtonImpl*)pHWPlatform->getButtonReset(), pContext);
  pButton->init(30);
  Task* pSweepingTask = new SweepingTask(
    pHWPlatform->getMotor(), 
    pHWPlatform->getSonarSensor(), 
    pHWPlatform->getLCDScreen(), 
    pHWPlatform->getPot(), pContext);
  pSweepingTask->init(80);

  sched.addTask(pBlinkingGreen);
  sched.addTask(pBlinkingRed);
  sched.addTask(pButton);
  sched.addTask(pSweepingTask);
#endif

#ifdef __TESTING_HW__
  /* Testing */
  Task* pTestHWTask = new TestHWTask(pHWPlatform);
  pTestHWTask->init(2000);
  sched.addTask(pTestHWTask);
#endif
}

void loop() {
    sched.schedule();
}