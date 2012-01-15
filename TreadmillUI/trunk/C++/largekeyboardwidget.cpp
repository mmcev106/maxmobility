#include "largekeyboardwidget.h"
#include "ui_largekeyboardwidget.h"

QString LargeKeyboardWidget::CUSTOM_KEYS[] = {"shift", ".", "/", "-"};
QRect LargeKeyboardWidget::KEY_RECT = QRect(42, 115, 86, 88.5);

LargeKeyboardWidget::LargeKeyboardWidget(QWidget* parent) :
    AbstractKeyboardWidget(KEY_RECT, parent, CUSTOM_KEYS)
    ,ui(new Ui::LargeKeyboardWidget)
{
    ui->setupUi(this);
    ui->backgroundLabel->lower();
}

LargeKeyboardWidget::~LargeKeyboardWidget(){
    delete ui;
}

InvisibleButton* LargeKeyboardWidget::getShiftButton(){
    return ui->invisibleButton_shift;
}

InvisibleButton* LargeKeyboardWidget::getEnterButton(){
    return ui->invisibleButton_enter;
}

QLineEdit* LargeKeyboardWidget::getInputBox(){
    return ui->inputBox;
}

void LargeKeyboardWidget::on_invisibleButton_space_pressed(){
    getInputBox()->setText(getInputBox()->text().append(" "));
}

void LargeKeyboardWidget::on_invisibleButton_deleteAll_pressed(){
    getInputBox()->setText("");
}
