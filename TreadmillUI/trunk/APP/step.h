#ifndef STEP_H
#define STEP_H

enum StepType { BASE_TYPE, SPEED_CHANGE_TYPE, GRADE_CHANGE_TYPE, WAIT_TYPE, END_TYPE };

class Step
{
public:
    Step();
    virtual StepType getType();
};

#endif // STEP_H
