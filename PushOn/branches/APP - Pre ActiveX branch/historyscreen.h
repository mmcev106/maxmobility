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
    void displayHistory(bool (*sortFunction)(HistoryItem*, HistoryItem*));
    bool (*lastSortFunction)(HistoryItem*, HistoryItem*);

    QList<HistoryItem*>* loadHistory();

    static QString DATE_FORMAT;
    int rowHeight;

    void resetHeaderImages();

private slots:
    void on_invisibleButton_6_pressed();
    void on_invisibleButton_date_pressed();
    void on_invisibleButton_workout_pressed();
    void on_invisibleButton_time_pressed();
    void on_invisibleButton_calories_pressed();
    void on_invisibleButton_distance_pressed();
    void on_invisibleButton_downArrowButton_pressed();
    void on_invisibleButton_upArrowButton_pressed();
};

#endif // HISTORYSCREEN_H
