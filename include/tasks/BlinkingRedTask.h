#ifndef __BLINKING_RED_TASK__
#define __BLINKING_RED_TASK__

#include "tasks/BlinkingTask.h"

class BlinkingRedTask : public BlinkingTask {
    public:
        BlinkingRedTask(Led* pLed, Context* pContext);
        void tick() override; 

    private:
};

#endif