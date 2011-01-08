#ifndef AUDIOSETTINGSWIDGET_H
#define AUDIOSETTINGSWIDGET_H

#include <QWidget>
#include "radiosliderwidget.h"
#include <QPushButton>
#include <QTimer>
#include <QFile>

namespace Ui {
    class AudioSettingsWidget;
}

class AudioSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioSettingsWidget(QWidget *parent = 0);
    ~AudioSettingsWidget();

private:
    Ui::AudioSettingsWidget *ui;

    QPixmap lineInPixmap;
    QPixmap fmPixmap;
    QPixmap usbPixmap;
    QPixmap feedbackPixmap;

    RadioSliderWidget fmSlider;
    QTimer pressTimer;
    QPushButton* lastButtonPressed;

    void presetButtonPressed(QPushButton* button);
    void presetButtonReleased(QPushButton* button);

private slots:
    void on_invisibleButton_preset_6_released();
    void on_invisibleButton_preset_5_released();
    void on_invisibleButton_preset_4_released();
    void on_invisibleButton_preset_3_released();
    void on_invisibleButton_preset_2_released();
    void on_invisibleButton_preset_1_released();
    void on_invisibleButton_preset_6_pressed();
    void on_invisibleButton_preset_5_pressed();
    void on_invisibleButton_preset_4_pressed();
    void on_invisibleButton_preset_3_pressed();
    void on_invisibleButton_preset_2_pressed();
    void on_invisibleButton_preset_1_pressed();
    void on_invisibleButton_feedback_pressed();
    void on_invisibleButton_usb_pressed();
    void on_invisibleButton_fm_pressed();
    void on_invisibleButton_lineIn_pressed();

    void pressTimerTimeout();
    void showFMWidgets();
    void hideFMWidgets();

    void saveRadioSettings();
    void loadRadioSettings();
    QFile* openRadioSettingsFile();
};

#endif // AUDIOSETTINGSWIDGET_H
