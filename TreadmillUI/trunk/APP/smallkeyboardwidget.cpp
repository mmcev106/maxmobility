#include "smallkeyboardwidget.h"
#include "ui_smallkeyboardwidget.h"

QString SmallKeyboardWidget::CUSTOM_KEYS[] = {"-", "[", "]", "_"};
QRect SmallKeyboardWidget::KEY_RECT = QRect(30, 74, 65, 67);

SmallKeyboardWidget::SmallKeyboardWidget(QWidget* parent ) :
    AbstractKeyboardWidget(KEY_RECT, parent, CUSTOM_KEYS)
    ,ui(new Ui::SmallKeyboardWidget)
{
    ui->setupUi(this);
    ui->backgroundLabel->lower();
}

SmallKeyboardWidget::~SmallKeyboardWidget(){
    delete ui;
}

InvisibleButton* SmallKeyboardWidget::getShiftButton(){
    return ui->invisibleButton_shift;
}

QLineEdit* SmallKeyboardWidget::getInputBox(){
    return ui->inputBox;
}
