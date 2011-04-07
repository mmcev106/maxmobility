#include "changespeedstep.h"

ChangeSpeedStep::ChangeSpeedStep(int speed)
{
    this->speed = speed;
}

StepType ChangeSpeedStep::getType(){
    return SPEED_CHANGE_TYPE;
}
