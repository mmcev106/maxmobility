#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H

#include <QWidget>

class AbstractScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractScreen(QWidget *parent = 0);

signals:

public slots:

};

#endif // ABSTRACTSCREEN_H
