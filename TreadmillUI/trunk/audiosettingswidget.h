#ifndef AUDIOSETTINGSWIDGET_H
#define AUDIOSETTINGSWIDGET_H

#include <QWidget>
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

private:
    Ui::AudioSettingsWidget *ui;

    QPixmap lineInPixmap;
    QPixmap fmPixmap;
    QPixmap usbPixmap;
    QPixmap feedbackPixmap;

    SliderWidget fmSlider;

private slots:
    void on_invisibleButton_feedback_pressed();
    void on_invisibleButton_usb_pressed();
    void on_invisibleButton_fm_pressed();
    void on_invisibleButton_lineIn_pressed();
};

#endif // AUDIOSETTINGSWIDGET_H
