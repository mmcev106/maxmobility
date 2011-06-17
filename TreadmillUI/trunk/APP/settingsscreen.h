#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>

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
};

#endif // SETTINGSSCREEN_H
