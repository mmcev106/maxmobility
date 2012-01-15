#ifndef LARGEKEYBOARDWIDGET_H
#define LARGEKEYBOARDWIDGET_H

#include "abstractkeyboardwidget.h"

namespace Ui {
    class LargeKeyboardWidget;
}

class LargeKeyboardWidget : public AbstractKeyboardWidget
{
    Q_OBJECT

public:
    LargeKeyboardWidget(QWidget* parent);
    ~LargeKeyboardWidget();
    InvisibleButton* getEnterButton();

protected:
    InvisibleButton* getShiftButton();
    QLineEdit* getInputBox();

private:
    Ui::LargeKeyboardWidget *ui;
    static QString CUSTOM_KEYS[];
    static QRect KEY_RECT;

private slots:
    void on_invisibleButton_space_pressed();
    void on_invisibleButton_deleteAll_pressed();
};

#endif // LARGEKEYBOARDWIDGET_H
