#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QTimer>

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
    int elapsedTime;
    QTimer *secondTimer;

private slots:
    void secondElapsed();
};

#endif // MAINSCREEN_H
