#include "tasks/SweepingTask.h"
#include <Arduino.h>
#include "kernel/Logger.h"
#include <avr/sleep.h>
#define FWD_TIME 2000
#define BWD_TIME 1000
#define START_TIME 100
#define RESET_TIME 500


SweepingTask::SweepingTask(
        ServoMotor* servo,
        Sonar* sonar,
        LCDScreen* screen,
        Potentiometer* pot,
        Context* pContext): 
    servoMotor(servo), sonar(sonar), screen(screen), pot(pot),
    context(pContext){
    setState(IDLE);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

float SweepingTask::readSonarWriteLCD() {
    const float dist = sonar->getDistance();
    screen->print("Detected: " + (dist == NO_OBJ_DETECTED ? "NO OBJECT" : (String)dist));
    return dist;
}

void SweepingTask::tick(){
    switch (state){    
    case IDLE: {
        if (this->checkAndSetJustEntered()){
            Logger.log(F("[SWT] IDLE"));
            context->setIDLE();
        }
        sleep_enable();
        sleep_mode();
        sleep_disable();
        setState(AUTOMATIC);
        context->setWORKING();
        break;
    }

    case AUTOMATIC: {
        static int angle = 0;
        static int diff = 1;
        const float dist = readSonarWriteLCD();
        if (this->checkAndSetJustEntered()) {
            log(F("[SWEEPING] AUTOMATIC"));
            angle = 0;
            diff = 1;
        }
        servoMotor->setPosition(angle);
        if (dist == NO_OBJ_DETECTED) return;
        if (dist > D2 && dist < D1) {
            context->setPRE_ALLARM();
        } else if (dist < D2) {
            context->setALLARM();
            setState(MANUAL);
        } else if (dist > D1 && context->inPreAllarm()) context->setWORKING();
        
        if (context->inPreAllarm()) diff = 2 * (diff/abs(diff));
        else diff = 1 * (diff/abs(diff));
        if (angle + diff > 180 || angle + diff < 0) diff = -diff;
        angle += diff;
    }
    
    case MANUAL: {
        this->readSonarWriteLCD();
        if (this->checkAndSetJustEntered()) {
            log(F("[SWEEPING] AUTOMATIC"));
        }
        pot->sync();
        servoMotor->setPosition(180*pot->getValue());
        if (!context->inAllarm()) setState(AUTOMATIC);
    }
  }
}

void SweepingTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long SweepingTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool SweepingTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}

void SweepingTask::log(const String& msg) {
    Logger.log(msg);
}