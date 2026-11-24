#ifndef __BLINKING_GREEN_TASK__
#define __BLINKING_GREEN_TASK__

#include "tasks/BlinkingTask.h"

class BlinkingGreenTask : public BlinkingTask {
    public:
        BlinkingGreenTask(Led* pLed, Context* pContext);
        void tick() override; 

    private:
};

#endif