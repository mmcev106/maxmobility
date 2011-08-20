#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"
#include <QDebug>
#include <QPainter>

#include "invisiblebutton.h"

KeyboardWidget::KeyboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyboardWidget)
    ,buttons()
{
    ui->setupUi(this);

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
    addKeyButton("-");
    addKeyButton("z");
    addKeyButton("x");
    addKeyButton("c");
    addKeyButton("v");
    addKeyButton("b");
    addKeyButton("n");
    addKeyButton("m");
    addKeyButton(".");
    addKeyButton("/");
    addKeyButton("_");

    ui->backgroundLabel->lower();
    show();
}

void KeyboardWidget::addKeyButton(QString c ){

    InvisibleButton* button = new InvisibleButton(this);
    button->setFixedSize(KEY_WIDTH,KEY_HEIGHT);
    button->setAccessibleName(c);

    int column = buttons.size()%KEYS_PER_ROW;
    int x = KEYS_START_X + column*KEY_WIDTH;

    int row = buttons.size()/KEYS_PER_ROW;
    int y = KEYS_START_Y + row*KEY_HEIGHT;

    button->move(x, y);
    button->show();

    connect( button, SIGNAL(pressed()), this, SLOT(buttonPressed() ));

    buttons.append(button);
}

void KeyboardWidget::buttonPressed(){
    QPushButton* button = (QPushButton*)sender();

    QString key = button->accessibleName();

    if(ui->invisibleButton_shift->isHighlighted()){
        key = key.toUpper();
        ui->invisibleButton_shift->setHighlighted(false);
    }

    ui->inputBox->setText(ui->inputBox->text().append(key));
}

KeyboardWidget::~KeyboardWidget()
{
    for(int i=0;i<buttons.size();i++){
        delete buttons.at(i);
    }

    delete ui;
}

void KeyboardWidget::on_invisibleButton_backspace_pressed()
{
    QString text = ui->inputBox->text();
    ui->inputBox->setText(text.left(text.length()-1));
}

void KeyboardWidget::on_invisibleButton_space_pressed()
{
    ui->inputBox->setText(ui->inputBox->text().append(' '));
}

void KeyboardWidget::on_invisibleButton_shift_pressed()
{
    ui->invisibleButton_shift->setHighlighted(!ui->invisibleButton_shift->isHighlighted());
    update();
}

QString KeyboardWidget::text(){
    return ui->inputBox->text();
}

void KeyboardWidget::setText(QString text){
    return ui->inputBox->setText(text);
}
