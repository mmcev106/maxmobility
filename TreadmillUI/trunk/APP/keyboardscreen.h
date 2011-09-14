#ifndef KEYBOARDSCREEN_H
#define KEYBOARDSCREEN_H

#include <QWidget>
#include "largekeyboardwidget.h"
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
    LargeKeyboardWidget keyboardWidget;

public slots:
    void on_enterButton_pressed();
    void on_invisibleButton_close_pressed();

};

#endif // KEYBOARDSCREEN_H
