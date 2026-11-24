#include "tasks/ButtonTask.h"
#include <Arduino.h>
#include <EnableInterrupt.h>
#include <kernel/Logger.h>

ButtonTask::ButtonTask(ButtonImpl* start, 
                       ButtonImpl* stop, 
                       ButtonImpl* reset, 
                       Context* context) :start(start), 
                                          stop(stop), 
                                          reset(reset), 
                                          context(context) {
    enableInterrupt(start->getPin(), {}, CHANGE);
    setState(IDLE);
}

void ButtonTask::tick() {
    switch (state)
    {
    case IDLE:
        if (context->inPreAllarm()) setState(PRE_ALLARM);
        break;
    case PRE_ALLARM:
        if (context->inAllarm()) setState(ALLARM);
        break;
    case ALLARM:
        if (reset->isPressed()) {
            setState(IDLE);
            context->setWORKING();
        }
        break;
    default:
        break;
    }
}

void ButtonTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long ButtonTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool ButtonTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}

void ButtonTask::log(const String& msg) {
    Logger.log(msg);
}                   