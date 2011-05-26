#include "state.h"



State::State() : state(NULL)
{
}

bool State::isSet(unsigned char mask){
    return (*state & mask) > 0;
}

void State::set(unsigned char mask){
    *state |= mask;
}

void State::unSet(unsigned char mask){
    if(isSet(mask)){
        *state -= mask;
    }
}

void State::setOn(){
    set(ON_OFF_MASK);
}

void State::setOff(){
    unSet(ON_OFF_MASK);
}

void State::setError(unsigned char errorTypeMask){
    *state = ERROR_MASK | errorTypeMask;
}


