#include "invisiblebutton.h"
#include <QPainter>
#include "preferences.h"

InvisibleButton::InvisibleButton(QWidget *parent) :
    QPushButton(parent)
    ,currentlyPressed(false)
    ,highlighted(false)
{
    setStyleSheet("border: none;");

    connect( this, SIGNAL(pressed()), this, SLOT(pressed() ));
    connect( this, SIGNAL(released()), this, SLOT(released() ));

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

void InvisibleButton::paintEvent(QPaintEvent *){

    if(currentlyPressed || isHighlighted()){
        QPainter qpainter (this);

        QPainterPath roundedRectPath;
        int padding = 5;
        roundedRectPath.addRoundedRect(padding, padding, width() - padding*2, height() - padding*2, 10, 10);

        qpainter.fillPath(roundedRectPath, HIGHLIGHT_BLUE);
    }
}
