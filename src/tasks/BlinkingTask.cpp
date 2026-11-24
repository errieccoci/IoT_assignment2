#include "tasks/BlinkingTask.h"
#include <Arduino.h>
#include "kernel/Logger.h"

BlinkingTask::BlinkingTask(Led* pLed, Context* pContext): 
    pLed(pLed), pContext(pContext){
    setState(IDLE);
}

void BlinkingTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long BlinkingTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

void BlinkingTask::log(const String& msg) {
    Logger.log(msg);
}

bool BlinkingTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}