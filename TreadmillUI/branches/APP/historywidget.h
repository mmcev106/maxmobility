#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

static const QString BIG_BRICK_URL = ":/images/images/big_brick.png";
static const QString HIGHLIGHTED_BIG_BRICK_URL = ":/images/images/big_brick_highlighted.png";

class HistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryWidget(QWidget *parent, int history[], int historyWidth, int historyHeight, QString brickImageUrl, QString highlightedBrickImageUrl);
    void setHistory(int*);
    int *history;

private:
    int length;
    void paintEvent(QPaintEvent *);

    QPixmap brickPixmap;
    QPixmap highlightedBrickPixmap;

signals:

public slots:

};

#endif // HISTORYWIDGET_H
