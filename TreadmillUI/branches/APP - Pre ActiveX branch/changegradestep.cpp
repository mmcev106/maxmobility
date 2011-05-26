#include "changegradestep.h"

ChangeGradeStep::ChangeGradeStep(float grade)
{
    this->grade = grade;
}

StepType ChangeGradeStep::getType(){
    return GRADE_CHANGE_TYPE;
}
