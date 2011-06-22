#include "scorewidget.h"

#include "ui_scorewidget.h"
#include <QString>


ScoreWidget::ScoreWidget(QWidget *parent, QString title, QString results) :
    QWidget(parent),
    ui(new Ui::ScoreWidget)

{
    ui->setupUi(this);
    ui->titleLabel->setText(title);
    ui->messageLabel->setText(results);
}

ScoreWidget::~ScoreWidget()
{
    ui->titleLabel->setText("");
    ui->messageLabel->setText("");
    delete ui;
}

void ScoreWidget::setText(QString title, QString results){
    ui->titleLabel->setText(title);
    ui->messageLabel->setText(results);
}
