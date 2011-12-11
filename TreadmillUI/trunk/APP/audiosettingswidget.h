#ifndef AUDIOSETTINGSWIDGET_H
#define AUDIOSETTINGSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QFile>
#include "sliderwidget.h"

namespace Ui {
    class AudioSettingsWidget;
}

class AudioSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioSettingsWidget(QWidget *parent = 0);
    ~AudioSettingsWidget();
    SliderWidget feedbackSlider;
    SliderWidget backgroundSlider;

private:
    Ui::AudioSettingsWidget *ui;
    QTimer *updateTimer;

private slots:
    void on_invisibleButton_close_pressed();
    void updateSoundLevels();
};

#endif // AUDIOSETTINGSWIDGET_H
