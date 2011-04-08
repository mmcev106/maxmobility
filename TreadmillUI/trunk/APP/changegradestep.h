#ifndef CHANGEGRADESTEP_H
#define CHANGEGRADESTEP_H

#include "step.h"

class ChangeGradeStep : public Step
{
public:
    ChangeGradeStep(float grade);
    float grade;
    StepType getType();
};

#endif // CHANGEGRADESTEP_H
