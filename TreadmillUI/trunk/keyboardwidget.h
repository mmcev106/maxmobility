#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

namespace Ui {
    class KeyboardWidget;
}

class KeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KeyboardWidget(QWidget *parent = 0);
    ~KeyboardWidget();

private:
    static const int KEYS_START_X = 32;
    static const int KEYS_START_Y = 76;

    static const int KEY_WIDTH = 60;
    static const int KEY_HEIGHT = 60;
    static const int KEYS_PER_ROW = 10;

    Ui::KeyboardWidget *ui;
    QList<QPushButton> buttons;
    void addKeyButton(char c );

};

#endif // KEYBOARDWIDGET_H
