#include "changespeedstep.h"

ChangeSpeedStep::ChangeSpeedStep(float speed)
{
    this->speed = speed;
}

StepType ChangeSpeedStep::getType(){
    return SPEED_CHANGE_TYPE;
}
