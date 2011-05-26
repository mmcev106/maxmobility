#ifndef WAITSTEP_H
#define WAITSTEP_H

#include "step.h"

class WaitStep : public Step
{
public:
    WaitStep(long time);
    long time;
    virtual StepType getType();
};

#endif // WAITSTEP_H
