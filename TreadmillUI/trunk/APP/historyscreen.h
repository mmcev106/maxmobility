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
    void updateArrowVisibility();

    QList<HistoryItem*>* loadHistory();

    static QString DATE_FORMAT;
    int rowHeight;

private slots:
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_downArrowButton_pressed();
    void on_invisibleButton_upArrowButton_pressed();
};

#endif // HISTORYSCREEN_H
