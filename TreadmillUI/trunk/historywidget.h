#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

class HistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryWidget(QWidget *parent, int history[], int historyWidth, int historyHeight);

private:
    int *history;
    int length;
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // HISTORYWIDGET_H
