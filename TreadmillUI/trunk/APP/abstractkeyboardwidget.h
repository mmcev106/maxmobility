#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include "invisiblebutton.h"
#include <QLineEdit>
#include <QTimer>

class AbstractKeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractKeyboardWidget(QRect keyRect, QWidget *parent = 0, QString customKeys[]=NULL);
    ~AbstractKeyboardWidget();
    QString text();
    void setText(QString);
    virtual InvisibleButton* getEnterButton() {}

protected:
    virtual InvisibleButton* getShiftButton() {}
    virtual QLineEdit* getInputBox() {}

private:
    int keyStartX;
    int keyStartY;
    int keyWidth;
    int keyHeight;
    static const int KEYS_PER_ROW = 10;

    QList<QPushButton*> buttons;
    void addKeyButton(QString c );

    qint64 backspaceDownTime;
    QTimer backspaceTimer;
    void deleteChars(int charsToRemove);
    const static int BACKSPACE_DELAY_1 = 200;
    const static int BACKSPACE_DELAY_2 = 500;
    const static int BACKSPACE_DELAY_3 = 1000;

protected slots:
    void on_invisibleButton_shift_pressed();
    void on_invisibleButton_space_pressed();
    void on_invisibleButton_backspace_pressed();
    void on_invisibleButton_backspace_released();
    void buttonPressed();

private slots:
    void backspaceTimerTimeout();

};

#endif // KEYBOARDWIDGET_H
