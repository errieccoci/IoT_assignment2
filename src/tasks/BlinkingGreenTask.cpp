#include "tasks/BlinkingGreenTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

BlinkingGreenTask::BlinkingGreenTask(Led* pLed, Context* pContext)
    : BlinkingTask(pLed, pContext) {}

void BlinkingGreenTask::tick() {
    switch (state)
    {
    case IDLE:
        if (this->checkAndSetJustEntered()) {
            pLed->switchOff();
            this->log(F("[BTGREEN] IDLE"));
        }
        if (!pContext->inIdle()) {
            this->setState(ON);
        }
        break;
    case ON:
        if (this->checkAndSetJustEntered()) {
            pLed->switchOn();
            this->log(F("[BTGREEN] ON"));
        }
        if (pContext->inIdle()) {
            this->setState(IDLE);
        }
        break;
    case OFF: 
        break;
    default:
        break;
    }
}