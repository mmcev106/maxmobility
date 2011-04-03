#include <limits>

#include "screens.h"

#include <QDateTime>
#include <QDebug>

 bool Screens::allowScreenShows = TRUE;

static int SCREEN_SHOW_THRESHOLD = 500;
long lastScreenShown = std::numeric_limits<long>::min();;

 void Screens::show(QWidget *screen){

     /**
      * Multiple pressed signals fire on mouse move events, which
      * causes multiple calls to show().  This check prevents the
      * show() calls from occurring on move events, until the
      * next release event.
      */
    if(allowScreenShows){
        long now = QDateTime::currentMSecsSinceEpoch();

        if(lastScreenShown < now - SCREEN_SHOW_THRESHOLD){

            qDebug() << now <<  " - Showing screen";
            lastScreenShown = now;
            screen->showFullScreen();
        }
        else{
            qDebug() << now <<  " - Ignoring show screen call";
        }
    }
}
