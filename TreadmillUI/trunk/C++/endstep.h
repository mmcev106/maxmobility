#ifndef ENDSTEP_H
#define ENDSTEP_H

#include "step.h"

class EndStep : public Step
{
public:
    EndStep(long time);
    long time;
    virtual StepType getType();
};

#endif // WAITSTEP_H
