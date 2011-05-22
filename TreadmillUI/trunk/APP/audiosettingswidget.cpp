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
    ,videoPixmap(":/images/images/Audio Screen - (Video).png")
    ,fmSlider(this)
//    ,pressTimer(this)
{
    ui->setupUi(this);
    ui->backgroundLabel->lower();

    fmSlider.move(-18, 286);
    fmSlider.step = .2;

    pressTimer.setSingleShot(true);
    pressTimer.setInterval(750);
    connect(&pressTimer, SIGNAL(timeout()), this, SLOT( pressTimerTimeout()));

    loadRadioSettings();

    on_invisibleButton_video_pressed();
}

AudioSettingsWidget::~AudioSettingsWidget()
{
    saveRadioSettings();
    delete ui;
}

void AudioSettingsWidget::saveRadioSettings(){

    QFile* file = openRadioSettingsFile();
    file->remove();
    file->open(QIODevice::ReadWrite);

    QTextStream stream(file);

    stream << fmSlider.value << endl;
    stream << endl;
    stream << ui->invisibleButton_preset_1->text() << endl;
    stream << ui->invisibleButton_preset_2->text() << endl;
    stream << ui->invisibleButton_preset_3->text() << endl;
    stream << ui->invisibleButton_preset_4->text() << endl;
    stream << ui->invisibleButton_preset_5->text() << endl;
    stream << ui->invisibleButton_preset_6->text() << endl;

    stream.flush();
    file->close();

    delete file;
}

void AudioSettingsWidget::loadRadioSettings(){

    QFile* file = openRadioSettingsFile();

    if(file->exists())
    {
        file->open(QIODevice::ReadOnly);
        QTextStream stream(file);

        fmSlider.setValue(QLocale(QLocale::C).toDouble(stream.readLine()));
        stream.readLine();
        ui->invisibleButton_preset_1->setText( stream.readLine() );
        ui->invisibleButton_preset_2->setText( stream.readLine() );
        ui->invisibleButton_preset_3->setText( stream.readLine() );
        ui->invisibleButton_preset_4->setText( stream.readLine() );
        ui->invisibleButton_preset_5->setText( stream.readLine() );
        ui->invisibleButton_preset_6->setText( stream.readLine() );

        stream.flush();
    }

    file->close();

    delete file;
}

QFile* AudioSettingsWidget::openRadioSettingsFile(){
    return new QFile("Radio Settings.txt");
}

void AudioSettingsWidget::on_invisibleButton_lineIn_pressed()
{
    hideFMWidgets();
    ui->backgroundLabel->setPixmap(lineInPixmap);
}

void AudioSettingsWidget::on_invisibleButton_fm_pressed()
{
    showFMWidgets();
    ui->backgroundLabel->setPixmap(fmPixmap);
}

void AudioSettingsWidget::on_invisibleButton_usb_pressed()
{
    hideFMWidgets();
    ui->backgroundLabel->setPixmap(usbPixmap);
}

void AudioSettingsWidget::on_invisibleButton_feedback_pressed()
{
    hideFMWidgets();
    ui->backgroundLabel->setPixmap(feedbackPixmap);
}

void AudioSettingsWidget::on_invisibleButton_video_pressed()
{
    hideFMWidgets();
    ui->backgroundLabel->setPixmap(videoPixmap);
}

void AudioSettingsWidget::hideFMWidgets(){

    fmSlider.hide();
    ui->invisibleButton_preset_1->hide();
    ui->invisibleButton_preset_2->hide();
    ui->invisibleButton_preset_3->hide();
    ui->invisibleButton_preset_4->hide();
    ui->invisibleButton_preset_5->hide();
    ui->invisibleButton_preset_6->hide();
}

void AudioSettingsWidget::showFMWidgets(){

    fmSlider.show();
    ui->invisibleButton_preset_1->show();
    ui->invisibleButton_preset_2->show();
    ui->invisibleButton_preset_3->show();
    ui->invisibleButton_preset_4->show();
    ui->invisibleButton_preset_5->show();
    ui->invisibleButton_preset_6->show();
}

void AudioSettingsWidget::presetButtonPressed(QPushButton* button)
{
    lastButtonPressed = button;
    pressTimer.start();
}

void AudioSettingsWidget::presetButtonReleased(QPushButton* button)
{
    if(pressTimer.isActive()){
        pressTimer.stop();

        if(!button->text().isEmpty()){
            fmSlider.setValue( QLocale(QLocale::C).toDouble( button->text() ));
        }
    }
}


void AudioSettingsWidget::pressTimerTimeout()
{
    lastButtonPressed->setText(QString("%1").arg(fmSlider.value));
}

void AudioSettingsWidget::on_invisibleButton_preset_1_pressed()
{
    presetButtonPressed(ui->invisibleButton_preset_1);
}

void AudioSettingsWidget::on_invisibleButton_preset_2_pressed()
{
    presetButtonPressed(ui->invisibleButton_preset_2);
}

void AudioSettingsWidget::on_invisibleButton_preset_3_pressed()
{
    presetButtonPressed(ui->invisibleButton_preset_3);
}

void AudioSettingsWidget::on_invisibleButton_preset_4_pressed()
{
    presetButtonPressed(ui->invisibleButton_preset_4);
}

void AudioSettingsWidget::on_invisibleButton_preset_5_pressed()
{
    presetButtonPressed(ui->invisibleButton_preset_5);
}

void AudioSettingsWidget::on_invisibleButton_preset_6_pressed()
{
    presetButtonPressed(ui->invisibleButton_preset_6);
}

void AudioSettingsWidget::on_invisibleButton_preset_1_released()
{
    presetButtonReleased(ui->invisibleButton_preset_1);
}

void AudioSettingsWidget::on_invisibleButton_preset_2_released()
{
    presetButtonReleased(ui->invisibleButton_preset_2);
}

void AudioSettingsWidget::on_invisibleButton_preset_3_released()
{
    presetButtonReleased(ui->invisibleButton_preset_3);
}

void AudioSettingsWidget::on_invisibleButton_preset_4_released()
{
    presetButtonReleased(ui->invisibleButton_preset_4);
}

void AudioSettingsWidget::on_invisibleButton_preset_5_released()
{
    presetButtonReleased(ui->invisibleButton_preset_5);
}

void AudioSettingsWidget::on_invisibleButton_preset_6_released()
{
    presetButtonReleased(ui->invisibleButton_preset_6);
}

void AudioSettingsWidget::on_invisibleButton_close_pressed()
{
    setVisible(false);
}
