#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QDate>
#include <QString>

class HistoryItem
{
public:
    HistoryItem();

    QDate date;
    QString name;
    short seconds;
    short calories;
    double distance;
};

#endif // HISTORYITEM_H
