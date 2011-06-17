#include "utils.h"

#include <QList>

#include <QDebug>
#include "workout.h"

int Utils::MAX_SPEED = MAX_SPEED_MPH;

Utils::Utils()
{
}

int Utils::getMAX_SPEED(){
    return MAX_SPEED;
}

void Utils::setMAX_SPEED(bool Standard){
    if (Standard==true)
        MAX_SPEED=MAX_SPEED_MPH;
    else
        MAX_SPEED=MAX_SPEED_KPH;
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

int Utils::CRC(char* msg, int len)
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


