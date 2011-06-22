#include "audiosettingswidget.h"
#include "ui_audiosettingswidget.h"
#include "preferences.h"
#include <QPixmap>

AudioSettingsWidget::AudioSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioSettingsWidget)
    ,activeButtonPixmap(":/images/images/Active Radio Button.png")
    ,checkPixmap(":/images/images/Check.png")
    ,crossPixmap(":/images/images/X.png")
{
    ui->setupUi(this);

    ui->label_internet->setVisible(Preferences::internetSoundEnabled);
    ui->label_usb->setVisible(Preferences::usbSoundEnabled);
    ui->label_lineIn->setVisible(Preferences::lineInEnabled);
    ui->label_video->setVisible(Preferences::videoSoundEnabled);
    ui->label_feedback->setVisible(Preferences::feedbackEnabled);
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
    Preferences::lineInEnabled = true;
    Preferences::videoSoundEnabled = false;
    Preferences::usbSoundEnabled = false;
    Preferences::internetSoundEnabled = false;
    update_radio_buttons();
}

void AudioSettingsWidget::on_invisibleButton_internet_pressed()
{
    Preferences::lineInEnabled = false;
    Preferences::videoSoundEnabled = false;
    Preferences::usbSoundEnabled = false;
    Preferences::internetSoundEnabled = true;
    update_radio_buttons();
}

void AudioSettingsWidget::on_invisibleButton_usb_pressed()
{
    Preferences::lineInEnabled = false;
    Preferences::videoSoundEnabled = false;
    Preferences::usbSoundEnabled = true;
    Preferences::internetSoundEnabled = false;
    update_radio_buttons();
}

void AudioSettingsWidget::on_invisibleButton_feedback_pressed()
{
    Preferences::feedbackEnabled = !Preferences::feedbackEnabled;
    update_radio_buttons();
}

void AudioSettingsWidget::on_invisibleButton_video_pressed()
{
    Preferences::lineInEnabled = false;
    Preferences::videoSoundEnabled = true;
    Preferences::usbSoundEnabled = false;
    Preferences::internetSoundEnabled = false;
    update_radio_buttons();
}

void AudioSettingsWidget::on_invisibleButton_close_pressed()
{
    setVisible(false);
}

void AudioSettingsWidget::update_radio_buttons()
{
    ui->label_internet->setVisible(Preferences::internetSoundEnabled);
    ui->label_usb->setVisible(Preferences::usbSoundEnabled);
    ui->label_lineIn->setVisible(Preferences::lineInEnabled);
    ui->label_video->setVisible(Preferences::videoSoundEnabled);
    if (Preferences::feedbackEnabled)
        ui->label_feedback->setPixmap(checkPixmap);
    else
        ui->label_feedback->setPixmap(crossPixmap);
}
