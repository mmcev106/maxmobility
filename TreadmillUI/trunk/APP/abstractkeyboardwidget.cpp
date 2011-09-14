#include "abstractkeyboardwidget.h"
#include "ui_keyboardwidget.h"
#include <QDebug>
#include <QPainter>

#include "invisiblebutton.h"

AbstractKeyboardWidget::AbstractKeyboardWidget(QRect keyRect, QWidget *parent, QString customKeys[]) :
    QWidget(parent)
    ,buttons()
{
    keyStartX = keyRect.x();
    keyStartY = keyRect.y();
    keyWidth = keyRect.width();
    keyHeight = keyRect.height();

    addKeyButton("1");
    addKeyButton("2");
    addKeyButton("3");
    addKeyButton("4");
    addKeyButton("5");
    addKeyButton("6");
    addKeyButton("7");
    addKeyButton("8");
    addKeyButton("9");
    addKeyButton("0");
    addKeyButton("q");
    addKeyButton("w");
    addKeyButton("e");
    addKeyButton("r");
    addKeyButton("t");
    addKeyButton("y");
    addKeyButton("u");
    addKeyButton("i");
    addKeyButton("o");
    addKeyButton("p");
    addKeyButton("a");
    addKeyButton("s");
    addKeyButton("d");
    addKeyButton("f");
    addKeyButton("g");
    addKeyButton("h");
    addKeyButton("j");
    addKeyButton("k");
    addKeyButton("l");
    addKeyButton(customKeys[0]);
    addKeyButton("z");
    addKeyButton("x");
    addKeyButton("c");
    addKeyButton("v");
    addKeyButton("b");
    addKeyButton("n");
    addKeyButton("m");
    addKeyButton(customKeys[1]);
    addKeyButton(customKeys[2]);
    addKeyButton(customKeys[3]);
}

void AbstractKeyboardWidget::addKeyButton(QString c ){

    InvisibleButton* button = new InvisibleButton(this);
    button->setFixedSize(keyWidth,keyHeight);
    button->setAccessibleName(c);

    int column = buttons.size()%KEYS_PER_ROW;
    int x = keyStartX + column*keyWidth;

    int row = buttons.size()/KEYS_PER_ROW;
    int y = keyStartY + row*keyHeight;

    button->move(x, y);
    button->show();

    connect( button, SIGNAL(pressed()), this, SLOT(buttonPressed() ));

    buttons.append(button);
}

void AbstractKeyboardWidget::buttonPressed(){
    QPushButton* button = (QPushButton*)sender();

    QString key = button->accessibleName();

    if(getShiftButton()->isHighlighted()){
        key = key.toUpper();
        getShiftButton()->setHighlighted(false);
    }

    getInputBox()->setText(getInputBox()->text().append(key));
}

AbstractKeyboardWidget::~AbstractKeyboardWidget()
{
    for(int i=0;i<buttons.size();i++){
        delete buttons.at(i);
    }
}

void AbstractKeyboardWidget::on_invisibleButton_backspace_pressed()
{
    QString text = getInputBox()->text();
    getInputBox()->setText(text.left(text.length()-1));
}

void AbstractKeyboardWidget::on_invisibleButton_space_pressed()
{
    getInputBox()->setText(getInputBox()->text().append(' '));
}

void AbstractKeyboardWidget::on_invisibleButton_shift_pressed()
{
    getShiftButton()->setHighlighted(!getShiftButton()->isHighlighted());
    update();
}

QString AbstractKeyboardWidget::text(){
    return getInputBox()->text();
}

void AbstractKeyboardWidget::setText(QString text){
    return getInputBox()->setText(text);
}
