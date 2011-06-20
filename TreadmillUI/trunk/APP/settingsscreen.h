#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT

public:
    static SettingsScreen* getSettingsScreen();
    static void createSettingsScreen(QWidget* parent);
    ~SettingsScreen();

private:
    static SettingsScreen* settingsScreen;

    explicit SettingsScreen(QWidget *parent = 0);
    Ui::SettingsScreen *ui;

    static int belt_time,on_time;
    QTimer *secondTimer;

private slots:
    void on_connect_invisibleButton_pressed();
    void updateDisplay();
};

#endif // SETTINGSSCREEN_H
