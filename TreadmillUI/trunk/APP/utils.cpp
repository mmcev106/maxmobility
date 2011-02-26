#include "utils.h"

Utils::Utils()
{
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
