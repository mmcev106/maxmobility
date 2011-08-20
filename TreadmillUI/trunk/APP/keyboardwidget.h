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
    QString text();
    void setText(QString);

private:
    static const int KEYS_START_X = 30;
    static const int KEYS_START_Y = 73;

    static const int KEY_WIDTH = 65;
    static const int KEY_HEIGHT = 67;
    static const int KEYS_PER_ROW = 10;

    Ui::KeyboardWidget *ui;
    QList<QPushButton*> buttons;
    void addKeyButton(QString c );

private slots:
    void on_invisibleButton_shift_pressed();
    void on_invisibleButton_space_pressed();
    void on_invisibleButton_backspace_pressed();
    void buttonPressed();

};

#endif // KEYBOARDWIDGET_H
