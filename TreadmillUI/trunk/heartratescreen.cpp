#include "heartratescreen.h"
#include "ui_heartratescreen.h"

#include "mainscreen.h"

int CONSTANT_HISTORY[12] = {15,15,15,15,15,15,15,15,15,15,15,15};
int DYNAMIC_HISTORY[12] = {9,9,26,26,9,9,26,26,9,9,26,26};

HeartRateScreen::HeartRateScreen(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::HeartRateScreen)
    ,weightSlider(this)
    ,ageSlider(this)
    ,timeSlider(this)
    ,lowSpeedSlider(this, 1, 15)
    ,highSpeedSlider(this, 1, 15)
    ,gradeHistoryWidget(this, CONSTANT_HISTORY, HISTORY_LENGTH, 26, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_DeleteOnClose );

    weightSlider.move(15,202);
    ageSlider.move(15,319);
    timeSlider.move(15,436);
    lowSpeedSlider.move(15,554);
    highSpeedSlider.move(15,671);

    gradeHistoryWidget.move(729,223);
    setConstantGrade();

    //Put the background behind the sliders
    ui->backgroundLabel->lower();
}

HeartRateScreen::~HeartRateScreen()
{
    delete ui;
}

void HeartRateScreen::setConstantGrade(){
    ui->constantSelectedLabel->setVisible(true);
    ui->dynamicSelectedLabel->setVisible(false);

    gradeHistoryWidget.setHistory(CONSTANT_HISTORY);
}

void HeartRateScreen::setDynamicGrade(){
    ui->constantSelectedLabel->setVisible(false);
    ui->dynamicSelectedLabel->setVisible(true);

    gradeHistoryWidget.setHistory(DYNAMIC_HISTORY);
}

void HeartRateScreen::on_invisibleButton_3_pressed()
{
    setConstantGrade();
}

void HeartRateScreen::on_invisibleButton_4_pressed()
{
    setDynamicGrade();
}

void HeartRateScreen::on_invisibleButton_6_pressed()
{
    MainScreen* w = new MainScreen(0);
     w->show();

     close();
}

void HeartRateScreen::on_invisibleButton_5_pressed()
{
    close();
}
