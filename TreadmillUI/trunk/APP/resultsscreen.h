#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H

#include <QWidget>

namespace Ui {
    class ResultsScreen;
}

class ResultsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsScreen(QWidget *parent, QString message);
    ~ResultsScreen();

private:
    Ui::ResultsScreen *ui;

private slots:
    void on_closeButton_pressed();
};

#endif // RESULTSSCREEN_H
