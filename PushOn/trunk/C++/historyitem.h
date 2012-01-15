#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QDateTime>
#include <QString>

class HistoryItem
{
public:
    HistoryItem();

    QDateTime date;
    QString name;
    short seconds;
    short calories;
    double distance;
};

#endif // HISTORYITEM_H
