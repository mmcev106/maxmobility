#include "audiosettingswidget.h"
#include "ui_audiosettingswidget.h"
#include <QPixmap>

AudioSettingsWidget::AudioSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioSettingsWidget)
    ,lineInPixmap(":/images/images/Audio Screen - (Line In).png")
    ,fmPixmap(":/images/images/Audio Screen - (FM).png")
    ,usbPixmap(":/images/images/Audio Screen - (USB).png")
    ,feedbackPixmap(":/images/images/Audio Screen - (Feedback).png")
    ,fmSlider(this, 87.5, 107.9)
{
    ui->setupUi(this);
    ui->backgroundLabel->lower();

    fmSlider.move(0, 235);
    fmSlider.step = .2;

    on_invisibleButton_lineIn_pressed();
}

AudioSettingsWidget::~AudioSettingsWidget()
{
    delete ui;
}

void AudioSettingsWidget::on_invisibleButton_lineIn_pressed()
{
    ui->backgroundLabel->setPixmap(lineInPixmap);
}

void AudioSettingsWidget::on_invisibleButton_fm_pressed()
{
    ui->backgroundLabel->setPixmap(fmPixmap);
}

void AudioSettingsWidget::on_invisibleButton_usb_pressed()
{
    ui->backgroundLabel->setPixmap(usbPixmap);
}

void AudioSettingsWidget::on_invisibleButton_feedback_pressed()
{
    ui->backgroundLabel->setPixmap(feedbackPixmap);
}
