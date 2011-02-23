#include "abstractscreen.h"
#include <QDebug>
#include <QMouseEvent>
#include "screens.h"

AbstractScreen::AbstractScreen(QWidget *parent) :
    QWidget(parent)
//    ,mouseTimer(this)
    ,mouseLabel(this)
{
    setAttribute( Qt::WA_DeleteOnClose );

    mouseTimer = new QTimer(this);
    mouseTimer->setSingleShot(false);
    mouseTimer->setInterval(100);
    connect(mouseTimer, SIGNAL(timeout()), this, SLOT( surroundCursor()));
    mouseTimer->start();

    mouseLabel.setStyleSheet("background-color: red;");
    mouseLabel.setFixedSize(10,10);
    mouseLabel.show();
}

void AbstractScreen::surroundCursor(){
    int x = QCursor::pos().x()+1;
    int y = QCursor::pos().y()+1 ;
    mouseLabel.move(x, y);
    mouseLabel.raise();
}

void QWidget::mouseMoveEvent( QMouseEvent * event ){
    Screens::allowScreenShows = FALSE;
}

void QWidget::mouseReleaseEvent( QMouseEvent * event ){
    Screens::allowScreenShows = TRUE;
}
