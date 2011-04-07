#ifndef CHANGESPEEDSTEP_H
#define CHANGESPEEDSTEP_H

#include "step.h"

class ChangeSpeedStep : public Step
{
public:
    ChangeSpeedStep(int speed);
    int speed;
    StepType getType();
};

#endif // CHANGESPEEDSTEP_H
