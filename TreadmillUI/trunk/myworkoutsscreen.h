#ifndef MYWORKOUTSSCREEN_H
#define MYWORKOUTSSCREEN_H

#include <QWidget>
#include "abstractscreen.h"

namespace Ui {
    class MyWorkoutsScreen;
}

class MyWorkoutsScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit MyWorkoutsScreen(QWidget *parent = 0);
    ~MyWorkoutsScreen();

private:
    Ui::MyWorkoutsScreen *ui;
    QPixmap workoutListItemBackground;

private slots:
    void on_invisibleButton_downArrowButton_pressed();
    void on_invisibleButton_upArrowButton_pressed();
    void on_invisibleButton_6_pressed();
};

#endif // MYWORKOUTSSCREEN_H
