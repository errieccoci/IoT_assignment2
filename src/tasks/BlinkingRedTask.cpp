#include "tasks/BlinkingRedTask.h"
#include <Arduino.h>
#include "kernel/Logger.h"


BlinkingRedTask::BlinkingRedTask(Led* pLed, Context* pContext)
    : BlinkingTask(pLed, pContext) {}

void BlinkingRedTask::tick() {
    switch (state)
    {
    case IDLE:
        if (this->checkAndSetJustEntered()) {
            pLed->switchOff();
            this->log(F("[BTRED] IDLE"));
        }
        if (pContext->inAllarm() || pContext->inPreAllarm()) {
            this->setState(ON);
        }
        break;
    case ON:
        if (this->checkAndSetJustEntered()) {
            pLed->switchOn();
            this->log(F("[BTRED] ON"));
        }
        if (pContext->inAllarm()) {
            this->setState(OFF);
        } else if(!pContext->inPreAllarm() && !pContext->inAllarm()) {
            this->setState(IDLE);
        }
        break;

    case OFF:
        if (this->checkAndSetJustEntered()) {
            pLed->switchOff();
            this->log(F("[BTRED] OFF"));
        }
        if (pContext->inAllarm() || pContext->inPreAllarm()) {
            this->setState(ON);
        } 
    default:
        break;
    }
}