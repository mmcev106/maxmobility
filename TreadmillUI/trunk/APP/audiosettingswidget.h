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
    void update_radio_buttons();
    Ui::AudioSettingsWidget *ui;

    QPixmap activeButtonPixmap;
    QPixmap checkPixmap;
    QPixmap crossPixmap;

private slots:
    void on_invisibleButton_close_pressed();
    void on_invisibleButton_video_pressed();
    void on_invisibleButton_feedback_pressed();
    void on_invisibleButton_usb_pressed();
    void on_invisibleButton_internet_pressed();
    void on_invisibleButton_lineIn_pressed();
};

#endif // AUDIOSETTINGSWIDGET_H
