#include "waitstep.h"

WaitStep::WaitStep(long time)
{
    this->time = time;
}

StepType WaitStep::getType(){
    return WAIT_TYPE;
}
