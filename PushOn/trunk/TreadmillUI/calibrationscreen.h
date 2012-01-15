#ifndef CALIBRATIONSCREEN_H
#define CALIBRATIONSCREEN_H

#include <QWidget>
#include <Qtimer>

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

    static int grade;
    QTimer *secondTimer;

private slots:
    void updateDisplay();
};

#endif // CALIBRATIONSCREEN_H
