#include "changegradestep.h"

ChangeGradeStep::ChangeGradeStep(int grade)
{
    this->grade = grade;
}

StepType ChangeGradeStep::getType(){
    return GRADE_CHANGE_TYPE;
}
