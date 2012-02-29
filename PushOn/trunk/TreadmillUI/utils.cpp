#include "utils.h"

#include <QList>

#include <QDebug>
#include "workout.h"
#include "preferences.h"

float Utils::MAX_SPEED = MAX_SPEED_MPH;
float Utils::DEF_SPEED = DEF_SPEED_MPH;

Phonon::MediaObject* Utils::accFeedback = NULL;
Phonon::AudioOutput* Utils::accOutput = NULL;

Phonon::MediaObject* Utils::backgroundMusic = NULL;
Phonon::AudioOutput* Utils::backgroundOutput = NULL;

Phonon::MediaObject* Utils::realTimeFeedback = NULL;
Phonon::AudioOutput* Utils::feedbackOutput = NULL;

//QAudioInput* Utils::qaudioInput = NULL;
//QAudioOutput* Utils::qaudioOutput = NULL;
//QIODevice* Utils::qdevice = NULL;

Utils::Utils()
{
}

QList<QUrl> playlist;
void Utils::InitAudio(QWidget* parent)
{

    accOutput = new Phonon::AudioOutput(Phonon::MusicCategory,parent);
    accFeedback = new Phonon::MediaObject(parent);
    Phonon::createPath(Utils::accFeedback,Utils::accOutput);

    backgroundOutput = new Phonon::AudioOutput(Phonon::MusicCategory,parent);
    backgroundMusic = new Phonon::MediaObject(parent);

    playlist = QList<QUrl>();
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL1.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL2.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL3.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL4.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL5.wav"));
    playlist.append(QUrl(AUDIO_ROOT_DIR+"PL6.wav"));

    Utils::backgroundMusic->setQueue(playlist);

//    backgroundMusic->setCurrentSource(AUDIO_ROOT_DIR + "background.wav");
    Phonon::createPath(backgroundMusic,backgroundOutput);
    backgroundMusic->play();

    realTimeFeedback = new Phonon::MediaObject(parent);
    feedbackOutput = new Phonon::AudioOutput(Phonon::MusicCategory,parent);
    Phonon::createPath(realTimeFeedback,feedbackOutput);

    backgroundOutput->setVolume(Preferences::backgroundSoundLevel/100);
    feedbackOutput->setVolume(Preferences::feedbackSoundLevel/100);
}

float Utils::getMAX_SPEED(){
    return MAX_SPEED;
}

void Utils::setMAX_SPEED(bool Standard){
    if (Standard==STANDARD_UNITS)
        MAX_SPEED=MAX_SPEED_MPH;
    else
        MAX_SPEED=MAX_SPEED_KPH;
}

float Utils::getDEF_SPEED(){
    return DEF_SPEED;
}

void Utils::setDEF_SPEED(bool Standard){
    if (Standard==STANDARD_UNITS)
        DEF_SPEED=DEF_SPEED_MPH;
    else
        DEF_SPEED=DEF_SPEED_KPH;
}


QString Utils::toString(unsigned char *array, int len){
    QString string;

    string = string.append( "{");
    for(int i=0;i<len;i++){

        if(i>0){
            string = string.append( ", ");
        }

       string = string.append(QString("%1").arg( array[i]));
    }
   string = string.append("}");

   return string;
}

int Utils::CRC(unsigned char* msg, int len)
{
    int crc = 65535;
    int i,j;
    for (i=0;i<len;i++)
    {
        crc ^= msg[i];
        for (j=0;j<8;j++)
        {
            if ( !(crc & 0x01) )
            {
                crc = crc>>1;
                crc &= 0x7FFF;
            }
            else
            {
                crc = crc>>1;
                crc &= 0x7FFF;
                crc ^= 0xA001;
            }
        }
    }
    return crc;
}


