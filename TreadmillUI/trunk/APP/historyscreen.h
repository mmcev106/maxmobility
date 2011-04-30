#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include <QWidget>
#include "abstractscreen.h"
#include <QList>
#include "historyitem.h"

namespace Ui {
    class HistoryScreen;
}

class HistoryScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit HistoryScreen(QWidget *parent = 0);
    ~HistoryScreen();

private:
    Ui::HistoryScreen *ui;
    QList<HistoryItem*>* history;

    void setUpArrowVisibility(bool);
    void setDownArrowVisibility(bool);

    QList<HistoryItem*>* loadHistory();

private slots:
    void on_invisibleButton_6_pressed();
};

#endif // HISTORYSCREEN_H
