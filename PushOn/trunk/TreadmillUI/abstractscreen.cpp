#include "abstractscreen.h"
#include <QDebug>
#include <QMouseEvent>
#include "screens.h"
#include "preferences.h"
#include <QMessageBox>
#include "utils.h"

AbstractScreen::AbstractScreen(QWidget *parent) :
    QWidget(parent)
//    ,mouseTimer(this)
    ,mouseLabel(this)
    ,accActionTimer(this)
    ,lastAccButtonPressed(NULL)
{
    setAttribute( Qt::WA_DeleteOnClose );

//    mouseTimer = new QTimer(this);
//    mouseTimer->setSingleShot(false);
//    mouseTimer->setInterval(100);
//    connect(mouseTimer, SIGNAL(timeout()), this, SLOT( surroundCursor()));
//    mouseTimer->start();

//    mouseLabel.setStyleSheet("background-color: red;");
//    mouseLabel.setFixedSize(10,10);
//    mouseLabel.show();

    setFocusPolicy(Qt::ClickFocus);
    setFocus();

    accActionTimer.setInterval(500);
    accActionTimer.setSingleShot(true);
}

void AbstractScreen::surroundCursor(){
    int x = QCursor::pos().x()+1;
    int y = QCursor::pos().y()+1 ;
    mouseLabel.move(x, y);
    mouseLabel.raise();
}

void QWidget::mouseMoveEvent( QMouseEvent * event ){
//    qDebug() << "mouse moved " << this;
    Screens::allowScreenShows = FALSE;
}

void QWidget::mouseReleaseEvent( QMouseEvent * event ){
//    qDebug() << "mouse released" << this;
    Screens::allowScreenShows = TRUE;
}

void AbstractScreen::keyPressEvent(QKeyEvent* event){

    bool eventConsumed = FALSE;

    if(Preferences::isTestingMode()){

        int key = event->key();

        if (key == Qt::Key_Escape){
            close();
            eventConsumed = TRUE;
        }
    }

    if(!eventConsumed){
        QWidget::keyPressEvent(event);
    }
}

/**
 * This method is meant is be called from button pressed methods that support accessibility.
 * If accessibility mode is enabled, the specified audio file is played on single clicks.
 *
 * If true is returned, the calling button should perform it's normal action.
 * If false is returned, the calling button should do nothing.
 */
bool AbstractScreen::handleAccAction(QString audioFile){

    if( Preferences::accessibilityMode ) {
        QObject* currentAccButton = QObject::sender();

        if(accActionTimer.isActive() && lastAccButtonPressed == currentAccButton){
            accActionTimer.stop();
            Utils::accFeedback->clear();
        }
        else{
            accActionTimer.stop();
            accActionTimer.start();
            Utils::accFeedback->clear();

            Utils::accFeedback->setCurrentSource(QString(AUDIO_ROOT_DIR + audioFile));
            Utils::accFeedback->play();

            lastAccButtonPressed = currentAccButton;

            return false;
        }
    }

    return true;
}
