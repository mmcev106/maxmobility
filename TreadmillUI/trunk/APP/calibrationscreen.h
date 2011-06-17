#ifndef CALIBRATIONSCREEN_H
#define CALIBRATIONSCREEN_H

#include <QWidget>

namespace Ui {
    class CalibrationScreen;
}

class CalibrationScreen : public QWidget
{
    Q_OBJECT

public:
    static CalibrationScreen* getCalibrationScreen();
    static void createCalibrationScreen(QWidget* parent);
    ~CalibrationScreen();

private:
    static CalibrationScreen* calibrationScreen;

    explicit CalibrationScreen(QWidget *parent = 0);
    Ui::CalibrationScreen *ui;
};

#endif // CALIBRATIONSCREEN_H
