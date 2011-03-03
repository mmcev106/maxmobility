#include "invisiblebutton.h"
#include <QPainter>
#include "preferences.h"
#include <QDebug>

InvisibleButton::InvisibleButton(QWidget *parent) :
    QPushButton(parent)
    ,currentlyPressed(false)
    ,highlighted(false)
    ,highlightOnPress(true)
    ,backgroundPixmap(NULL)
{
    setStyleSheet("border: none;");

    connect( this, SIGNAL(pressed()), this, SLOT(pressed() ));
    connect( this, SIGNAL(released()), this, SLOT(released() ));

    setFocusPolicy(Qt::NoFocus);
}

void InvisibleButton::pressed(){
    currentlyPressed = true;
    update();
}
void InvisibleButton::released(){
    currentlyPressed = false;
    update();
}

bool InvisibleButton::isHighlighted(){
    return highlighted;
}

void InvisibleButton::setHighlighted(bool highlighted){
   this->highlighted=highlighted;
   update();
}

void InvisibleButton::setVisible(bool visible){
    QPushButton::setVisible(visible);

    if(visible == false){
        currentlyPressed = false;
    }
}


void InvisibleButton::paintEvent(QPaintEvent * event){

    if(backgroundPixmap != NULL){
        QPainter qpainter (this);
        qpainter.drawPixmap(0,0, *backgroundPixmap);
    }

    QPushButton::paintEvent(event);

    if( (highlightOnPress && currentlyPressed) || isHighlighted()){
        QPainter qpainter (this);

        QPainterPath roundedRectPath;
        int padding = 5;
        roundedRectPath.addRoundedRect(padding, padding, width() - padding*2, height() - padding*2, 10, 10);

        qpainter.fillPath(roundedRectPath, HIGHLIGHT_BLUE);
    }
}


void InvisibleButton::setBackgroundPixmap(QPixmap* backgroundPixmap){
    this->backgroundPixmap = backgroundPixmap;
    setFixedSize(backgroundPixmap->size());
}
