#ifndef KEYBOARDSCREEN_H
#define KEYBOARDSCREEN_H

#include <QWidget>
#include "keyboardwidget.h"
#include "abstractscreen.h"

namespace Ui {
    class KeyboardScreen;
}

class KeyboardScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit KeyboardScreen(QString text, QWidget* targetWidget);
    ~KeyboardScreen();

private:
    Ui::KeyboardScreen *ui;
    QWidget* targetWidget;
    KeyboardWidget keyboardWidget;


private slots:
    void on_clearButton_pressed();
    void on_invisibleButton_close_pressed();
    void on_doneButton_pressed();
};

#endif // KEYBOARDSCREEN_H
