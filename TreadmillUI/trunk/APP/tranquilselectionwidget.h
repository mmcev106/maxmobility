#ifndef TRANQUILSELECTIONWIDGET_H
#define TRANQUILSELECTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

namespace Ui {
    class TranquilSelectionWidget;
}

class TranquilSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TranquilSelectionWidget(QWidget *parent = 0);
    ~TranquilSelectionWidget();

private:
    Ui::TranquilSelectionWidget *ui;

    QPushButton* lastButtonPressed;

private slots:
    void on_ducks_invisibleButton_pressed();
    void on_fish_invisibleButton_pressed();
    void on_ocean_invisibleButton_pressed();
    void on_waterfall_invisibleButton_pressed();
};

#endif // TRANQUILSELECTIONWIDGET_H
