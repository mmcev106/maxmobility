#include "serialsenderthread.h"
#include <QDebug>
#include "preferences.h"
#include "utils.h"
#include "state.h"

static int MESSAGE_DELAY = 100;

SerialSenderThread::SerialSenderThread(QextSerialPort* port)
{
    this->port = port;
}

void SerialSenderThread::run(){

    unsigned char* messageData = new unsigned char[10];

    messageData[0] = 0xFF;
    messageData[MESSAGE_LENGTH-1] = '\n';
    int crc;

    while(port->isOpen()){
        unsigned char _state = Preferences::sendState.sendstate;
        messageData[1] = _state;
        Preferences::sendState.sendstate &=(~(STATE_CHANGE_MASK));

        if ( (_state&CALIBRATING_MASK) && (!(_state&ERROR_MASK)) )			// treadmill is in CALIBRATION state
        {
            messageData[2] 	= 0;        // was command
            messageData[3] 	= 0;
            messageData[4] 	= 0;
        }
        else
        {
            if ( _state&SETUP_MASK )		// treadmill is in SETUP state
            {
                messageData[2] 	= 0;  // need to set to reflect units from radio button
                messageData[3] 	= 0;
                messageData[4] 	= 0;
            }
            else
            {
                if ( _state&ON_OFF_MASK || (!(_state&CALIBRATING_MASK) && !(_state&SETUP_MASK)) )		// treadmill is either in ON or OFF state
                {

                    messageData[2] 	= Preferences::heartRate;

                    messageData[3] 	= Preferences::spd_diff;
                    Preferences::spd_diff=0;

                    messageData[4] 	= Preferences::grd_diff;
                    Preferences::grd_diff=0;
                }
            }
        }
        crc 	= Utils::CRC(messageData,5);
        messageData[5] = (crc>>8)&0xFF;
        messageData[6] = crc&0xFF;

//        qDebug() << "Sending: " << Utils::toString( messageData, MESSAGE_LENGTH );
        Preferences::hasSentState = true;
        port->write((char*)messageData,8);
        port->flush();

        msleep(MESSAGE_DELAY);
    }
}
