#ifndef SMALLKEYBOARDWIDGET_H
#define SMALLKEYBOARDWIDGET_H

#include "abstractkeyboardwidget.h"

namespace Ui {
    class SmallKeyboardWidget;
}

class SmallKeyboardWidget : public virtual AbstractKeyboardWidget
{
public:
    SmallKeyboardWidget(QWidget* parent);
    ~SmallKeyboardWidget();

protected:
    InvisibleButton* getShiftButton();
    QLineEdit* getInputBox();

private:
    Ui::SmallKeyboardWidget *ui;
    static QString CUSTOM_KEYS[];
    static QRect KEY_RECT;
};

#endif // SMALLKEYBOARDWIDGET_H
