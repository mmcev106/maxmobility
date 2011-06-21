#ifndef TRAILSELECTIONWIDGET_H
#define TRAILSELECTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

namespace Ui {
    class TrailSelectionWidget;
}

class TrailSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrailSelectionWidget(QWidget *parent = 0);
    ~TrailSelectionWidget();

private:
    Ui::TrailSelectionWidget *ui;

    QPushButton* lastButtonPressed;

private slots:
    void on_radnor_invisibleButton_pressed();
    void on_couchville_invisibleButton_pressed();
    void on_deer_invisibleButton_pressed();
    void on_nashville_invisibleButton_pressed();
};

#endif // TRAILSELECTIONWIDGET_H
