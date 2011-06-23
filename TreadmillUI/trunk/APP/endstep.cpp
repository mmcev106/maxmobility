#include "endstep.h"

EndStep::EndStep(long time)
{
    this->time = time;
}

StepType EndStep::getType(){
    return END_TYPE;
}
