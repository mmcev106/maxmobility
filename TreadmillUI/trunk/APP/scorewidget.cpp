#include "scorewidget.h"

#include "ui_scorewidget.h"

ScoreWidget::ScoreWidget(QWidget *parent, QString title, QString results) :
    QWidget(parent),
    ui(new Ui::ScoreWidget)

{
    ui->titleLabel->setText(title);
    ui->messageLabel->setText(results);
}

ScoreWidget::~AudioSettingsWidget()
{
    ui->titleLabel->setText("");
    ui->messageLabel->setText("");
    delete ui;
}
