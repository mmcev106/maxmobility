#ifndef STATE_H
#define STATE_H

#include <QString>

static const unsigned char ON_OFF_MASK = (1<<0);
static const unsigned char CALIBRATING_MASK = (1<<1);
static const unsigned char SETUP_MASK = (1<<2);
static const unsigned char ACCESSIBILITY_MASK = (1<<3);
static const unsigned char UNITS_MASK = (1<<4);
static const unsigned char STATE_CHANGE_MASK = (1<<6);
static const unsigned char ERROR_MASK = (1<<7);

static const unsigned char EM_STOP_ERROR_MASK = 1;
static const unsigned char TOE_SAFETY_ERROR_MASK = 2;
static const unsigned char SPEED_CONTROL_ERROR_MASK = 4;
static const unsigned char GRADE_CONTROL_ERROR_MASK = 8;
static const unsigned char SERIAL_RECEIVING_ERROR_MASK = 16;
static const unsigned char SERIAL_SENDING_ERROR_MASK = 32;
static const unsigned char CRITICAL_ERROR_MASK = 64;

class State
{
public:
    State();

    void setOn();
    void setOff();
    void setError(unsigned char);

    static unsigned char state;

private:
    void set(unsigned char mask);
    void unSet(unsigned char mask);
    bool isSet(unsigned char mask);
};

#endif // STATE_H
