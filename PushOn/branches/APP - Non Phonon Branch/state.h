#ifndef STATE_H
#define STATE_H

#include <QString>

class State
{
public:
    State();

    void setOn();
    void setOff();
    void setError(unsigned char);

    static const unsigned char ON_OFF_MASK = 1;
    static const unsigned char WAKE_SLEEP_MASK = 2;
    static const unsigned char CALIBRATING_MASK = 4;
    static const unsigned char SETUP_MASK = 8;
    static const unsigned char ACCESSIBILITy_MASK = 16;
    static const unsigned char PROFILE_MANUAL_MASK = 32;
    static const unsigned char ERROR_MASK = 128;

    static const unsigned char EM_STOP_ERROR_MASK = 1;
    static const unsigned char TOE_SAFETY_ERROR_MASK = 2;
    static const unsigned char SPEED_CONTROL_ERROR_MASK = 4;
    static const unsigned char GRADE_CONTROL_ERROR_MASK = 8;
    static const unsigned char SERIAL_RECEIVING_ERROR_MASK = 16;
    static const unsigned char SERIAL_SENDING_ERROR_MASK = 32;
    static const unsigned char CRITICAL_ERROR_MASK = 64;

    unsigned char* state;

private:
    void set(unsigned char mask);
    void unSet(unsigned char mask);
    bool isSet(unsigned char mask);
};

#endif // STATE_H
