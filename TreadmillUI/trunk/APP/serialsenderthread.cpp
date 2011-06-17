#include "serialsenderthread.h"
#include <QDebug>
#include "preferences.h"
#include "utils.h"
#include "state.h"

static int MESSAGE_DELAY = 100;

SerialSenderThread::SerialSenderThread()
{
}

void SerialSenderThread::run(){

    QextSerialPort* port =  Preferences::serialPort;

    unsigned char* messageData = new unsigned char[10];

    messageData[0] = 0xFF;
    messageData[MESSAGE_LENGTH-1] = '\n';
    int crc;

    while(true){
        unsigned char _state = Preferences::sendState.state;
        messageData[1] = _state;
        if ( _state&CALIBRATING_MASK && !_state&ERROR_MASK )			// treadmill is in CALIBRATION state
        {
            Preferences::sendState.state &=(~(STATE_CHANGE_MASK));

            messageData[2] 	= 0;        // was command
            messageData[3] 	= 0;
            messageData[4] 	= 0;
        }
        else
        {
            if ( _state&SETUP_MASK )		// treadmill is in SETUP state
            {
                Preferences::sendState.state &=(~(STATE_CHANGE_MASK));

                messageData[2] 	= Preferences::command;  // need to set to reflect units from radio button
                messageData[3] 	= 0;
                messageData[4] 	= 0;
            }
            else
            {
                if ( _state&ON_OFF_MASK || (!(_state&CALIBRATING_MASK) && !(_state&SETUP_MASK)) )		// treadmill is either in ON or OFF state
                {
                    Preferences::sendState.state &=(~(STATE_CHANGE_MASK));

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

        qDebug() << "Sending: " << Utils::toString( messageData, MESSAGE_LENGTH );
        port->write((char*)messageData,8);
        port->flush();

        msleep(MESSAGE_DELAY);
    }
}
