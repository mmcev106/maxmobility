#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

namespace Ui {
    class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0, QString action = "");
    ~MainScreen();

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
