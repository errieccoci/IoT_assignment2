#include <model/Context.h>
#include <Arduino.h>
#include "kernel/Task.h"
#include <devices/ButtonImpl.h>

#ifndef __BUTTONTASK__
#define __BUTTONTASK__

class ButtonTask: public Task {
    public:
        ButtonTask(ButtonImpl* start, ButtonImpl* stop, ButtonImpl* reset, Context* context);
        void tick();
    protected:
        void setState(int state);
        long elapsedTimeInState();
        void log(const String& msg);
        void empty();
        bool checkAndSetJustEntered();
        
        enum { IDLE, PRE_ALLARM, ALLARM };
        int state;
        long stateTimestamp;
        bool justEntered;

        ButtonImpl* start;
        ButtonImpl* stop;
        ButtonImpl* reset;
        Context* context;
};
#endif