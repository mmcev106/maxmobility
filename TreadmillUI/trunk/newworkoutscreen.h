#ifndef NEWWORKOUTSCREEN_H
#define NEWWORKOUTSCREEN_H

#include <QWidget>
#include "abstractscreen.h"
#include "keyboardwidget.h"

namespace Ui {
    class NewWorkoutScreen;
}

class NewWorkoutScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit NewWorkoutScreen(QWidget *parent = 0);
    ~NewWorkoutScreen();

private:
    Ui::NewWorkoutScreen *ui;
    KeyboardWidget keyboardWidget;
};

#endif // NEWWORKOUTSCREEN_H
