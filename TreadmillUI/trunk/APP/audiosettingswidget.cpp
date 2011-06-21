#include "audiosettingswidget.h"
#include "ui_audiosettingswidget.h"
#include <QPixmap>

AudioSettingsWidget::AudioSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioSettingsWidget)
    ,activeButtonPixmap(":/images/images/Active Radio Button.png")
    ,checkPixmap(":/images/images/Check.png")
    ,crossPixmap(":/images/images/X.png")
{
    ui->setupUi(this);

    ui->label_internet->setVisible(false);
    ui->label_usb->setVisible(false);
    ui->label_lineIn->setVisible(false);
    ui->label_video->setVisible(true);
    ui->label_feedback->setVisible(true);
    ui->label_feedback->setPixmap(checkPixmap);


    ui->label_internet->lower();
    ui->label_usb->lower();
    ui->label_lineIn->lower();
    ui->label_video->lower();
    ui->label_feedback->lower();
    ui->backgroundLabel->lower();
    ui->blackBackgroundLabel->lower();
}

AudioSettingsWidget::~AudioSettingsWidget()
{
    delete ui;
}

void AudioSettingsWidget::on_invisibleButton_lineIn_pressed()
{
    hide_radio_buttons();
    ui->label_lineIn->setVisible(true);
}

void AudioSettingsWidget::on_invisibleButton_internet_pressed()
{
    hide_radio_buttons();
    ui->label_internet->setVisible(true);
}

void AudioSettingsWidget::on_invisibleButton_usb_pressed()
{
    hide_radio_buttons();
    ui->label_usb->setVisible(true);
}

void AudioSettingsWidget::on_invisibleButton_feedback_pressed()
{
    ui->label_feedback->setPixmap(crossPixmap);
}

void AudioSettingsWidget::on_invisibleButton_video_pressed()
{
    hide_radio_buttons();
    ui->label_video->setVisible(true);
}

void AudioSettingsWidget::on_invisibleButton_close_pressed()
{
    setVisible(false);
}

void AudioSettingsWidget::hide_radio_buttons()
{
    ui->label_internet->setVisible(false);
    ui->label_usb->setVisible(false);
    ui->label_lineIn->setVisible(false);
    ui->label_video->setVisible(false);
}
