#include "messagescreen.h"
#include "ui_messagescreen.h"

#include "preferences.h"

static int counter = 0;

MessageScreen::MessageScreen(QWidget *parent, QString message) :
    AbstractScreen(parent),
    ui(new Ui::MessageScreen)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose, false );

    ui->messageLabel->setText(message);
}

MessageScreen::~MessageScreen()
{
    delete ui;
}

void MessageScreen::keyPressEvent(QKeyEvent* event){

    bool eventConsumed = FALSE;

    if(Preferences::isTestingMode()){

        if(event->key() == Qt::Key_P){

            eventConsumed = TRUE;

            if(MainScreen::getMainScreen()->isWorkoutPaused()){
                MainScreen::getMainScreen()->unPauseWorkout();
            }
            else{
                MainScreen::getMainScreen()->pauseWorkout();
            }
        }
    }

    if(!eventConsumed){
        AbstractScreen::keyPressEvent(event);
    }
}

