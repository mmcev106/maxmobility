#include "keyboardscreen.h"
#include "ui_keyboardscreen.h"
#include <QDebug>
#include "screens.h"
#include <QKeyEvent>

KeyboardScreen::KeyboardScreen(QString text, QWidget* targetWidget) :
    AbstractScreen(),
    ui(new Ui::KeyboardScreen)
    ,keyboardWidget(this)
{
    ui->setupUi(this);

    this->targetWidget = targetWidget;

    keyboardWidget.setText(text);
    keyboardWidget.move(156, 100);
    keyboardWidget.raise();
}

KeyboardScreen::~KeyboardScreen()
{
    delete ui;
}

void KeyboardScreen::on_invisibleButton_close_pressed(){
    close();
}

void KeyboardScreen::on_doneButton_pressed()
{
    QKeyEvent *event;

    /**
     * Delete any existing characters on either side of the cursor
     */
    for(int i=0; i<500; i++){
        event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
        QCoreApplication::postEvent (targetWidget, event);

        event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
        QCoreApplication::postEvent (targetWidget, event);
    }


    QString text = keyboardWidget.text();

    event = new QKeyEvent ( QEvent::KeyPress, 0, Qt::NoModifier, text);
    QCoreApplication::postEvent (targetWidget, event);

    close();
}

void KeyboardScreen::on_clearButton_pressed()
{
    keyboardWidget.setText("");
}
