#include "seriallistenerthread.h"

#include "qdebug.h"
#include "preferences.h"
#include "qextserialport.h"
#include "upperboardevent.h"
#include "QApplication"
#include "utils.h"
#include "calibrationscreen.h"
#include "settingsscreen.h"
#include "startupwindow.h"

static const int READ_WAIT_LIMIT = 0;//1000 * 60 * 5

SerialListenerThread::SerialListenerThread()
{
}

void SerialListenerThread::run(){

    QextSerialPort* port =  Preferences::serialPort;

    while(port->isOpen()){     //port->waitForReadyRead( READ_WAIT_LIMIT )
        QByteArray data = port->read(MESSAGE_LENGTH);

        if(data.length() < 100 && data.length() > 0){
            qDebug() << "Received Data: " << Utils::toString ( (unsigned char* )data.data(), data.length());
        }


        if(data.length() != MESSAGE_LENGTH){
            qDebug() << "The message received was not the correct length!  It was " << data.length() << " bytes long.";
        }
        else{
            handleMessage((unsigned  char*)data.data());
        }

        QThread::msleep(100);
    }
}

void SerialListenerThread::handleMessage(unsigned char* data){

    if(data[0] != 0xFF){
        qDebug() << "Ignoring message because the first byte was not 0xFF";
        return;
    }

    unsigned char _state = (~STATE_CHANGE_MASK)&data[1];
    char heartRate = data[2];
    char speed = data[3];
    char grade = data[4];  // Wes updated these to speed and grade from cadence and rawData
    int crcMsb = data[5];
    int crcLsb = data[6];

    if(data[7] != '\n'){
        qDebug() << "Ignoring message because the last byte was not a new line!";
        return;
    }
    int _crc = crcMsb*256 + crcLsb;
    if (_crc != Utils::CRC(data,5))
    {
        qDebug() << "Ignoring message because the CRC's didn't match!";
        qDebug() << "MSG CRC = " << _crc;
        qDebug() << "My CRC = " << Utils::CRC(data,5);
        return;
    }

    if (Preferences::getCurrentState() != _state)
    {
        // do state-based screen switching here!
        if (Preferences::getCurrentState()&CALIBRATING_MASK)
            CalibrationScreen::getCalibrationScreen()->setVisible(false);
        else if (Preferences::getCurrentState()&SETUP_MASK)
            SettingsScreen::getSettingsScreen()->setVisible(false);
        else if (Preferences::getCurrentState()&ON_OFF_MASK)
            MainScreen::getMainScreen()->endWorkout();
    }

    Preferences::updateCurrentState(_state);

    if ( _state&ON_OFF_MASK || ( !(_state&CALIBRATING_MASK) && !(_state&SETUP_MASK) ) )
    {
        Preferences::updateCurrentGrade(grade);
        Preferences::updateCurrentSpeed(speed);
        Preferences::setHeartRate(heartRate);
        if (_state&ON_OFF_MASK)
        {
            if (!MainScreen::getMainScreen()->isVisible())
            {
                MainScreen::getMainScreen()->setVisible(true);
                MainScreen::getMainScreen()->startWorkout(Preferences::currentWorkout);
            }
        }
    }
    if ( _state&CALIBRATING_MASK )
    {
        CalibrationScreen::getCalibrationScreen()->setVisible(true);
        Preferences::updateCurrentGrade(data[4]);
    }
    if ( _state&SETUP_MASK )
    {
        SettingsScreen::getSettingsScreen()->setVisible(true);
        if ( _state&UNITS_MASK)
        {
            Preferences::setMeasurementSystem(STANDARD);
        }
        else
        {
            Preferences::setMeasurementSystem(METRIC);
        }
        if ( data[2]&0x01 )
            Preferences::on_time = (data[3]<<8) | (data[4]);
        else
            Preferences::belt_time = (data[3]<<8) | (data[4]);
    }

//    UpperBoardEvent event(heartRate, speed, grade); // wes updated this to speed and grade from cadence
//    QApplication::sendEvent(Preferences::application,  &event);

    // Update History widgets

}
