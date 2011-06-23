#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class ResultsScreen;
}

static const int FIRST_TIMEOUT = 2;
static const int CLOSE_TIMEOUT = 7;

class ResultsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsScreen(QWidget *parent, QString message);
    ~ResultsScreen();

private:
    Ui::ResultsScreen *ui;
    QTimer *secondTimer;

private slots:
    void on_closeButton_pressed();
    void secondTimerTimeout();
};

#endif // RESULTSSCREEN_H
