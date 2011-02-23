#include "screens.h"

#include <QDateTime>
#include <QDebug>

 bool Screens::allowScreenShows = TRUE;

static int SCREEN_SHOW_THRESHOLD = 100;

 void Screens::show(QWidget *screen){

     /**
      * Multiple pressed signals fire on mouse move events, which
      * causes multiple calls to show().  This check prevents the
      * show() calls from occurring on move events, until the
      * next release event.
      */
    if(allowScreenShows){
        screen->showFullScreen();
    }
}
