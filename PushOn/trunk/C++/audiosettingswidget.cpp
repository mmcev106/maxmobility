#include "audiosettingswidget.h"
#include "ui_audiosettingswidget.h"
#include "preferences.h"
#include "utils.h"
#include <QPixmap>

AudioSettingsWidget::AudioSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioSettingsWidget)
    ,feedbackSlider(this, 0.0, 100.0)
    ,backgroundSlider(this, 0.0, 100.0)
    ,updateTimer(new QTimer(this))
{
    ui->setupUi(this);

    connect(updateTimer,SIGNAL(timeout()), this, SLOT( updateSoundLevels()));
    updateTimer->setSingleShot(false);
    updateTimer->setInterval(10);  // every 10 ms

    feedbackSlider.setFixedWidth(545);
    backgroundSlider.setFixedWidth(545);

    feedbackSlider.setValue(Preferences::feedbackSoundLevel);
    backgroundSlider.setValue(Preferences::backgroundSoundLevel);

    feedbackSlider.move(25, 223);
    backgroundSlider.move(25, 345);

    feedbackSlider.initialize();
    backgroundSlider.initialize();

    ui->backgroundLabel->lower();
    ui->blackBackgroundLabel->lower();

    updateTimer->start();
}

AudioSettingsWidget::~AudioSettingsWidget()
{
    delete ui;
}

void AudioSettingsWidget::on_invisibleButton_close_pressed()
{
    setVisible(false);
}

void AudioSettingsWidget::updateSoundLevels()
{
    Preferences::feedbackSoundLevel = feedbackSlider.value;
    Preferences::backgroundSoundLevel = backgroundSlider.value;

    Utils::feedbackOutput->setVolume(Preferences::feedbackSoundLevel/100.0);
    Utils::backgroundOutput->setVolume(Preferences::backgroundSoundLevel/100.0);
}
