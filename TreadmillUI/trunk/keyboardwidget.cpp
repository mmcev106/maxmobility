#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"

KeyboardWidget::KeyboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyboardWidget)
    ,buttons()
{
    ui->setupUi(this);

    addKeyButton('1');
}

void KeyboardWidget::addKeyButton(char c ){

    QPushButton* button = new QPushButton(this);
    button->setFixedSize(KEY_WIDTH,KEY_HEIGHT);

    int column = buttons.size()%KEYS_PER_ROW;
    int x = column*KEY_WIDTH;

    int row = buttons.size()/KEYS_PER_ROW;
    int y = row*KEY_HEIGHT;

    buttons.move(x, y);

}

KeyboardWidget::~KeyboardWidget()
{
    delete ui;
}
