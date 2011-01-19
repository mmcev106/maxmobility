#include "historywidget.h"
#include <QPainter>
#include <QDebug>

static int VERTICAL_PADDING = 1;
static int HORIZONTAL_PADDING = 3;

HistoryWidget::HistoryWidget(QWidget *parent,int history[], int historyWidth, int historyHeight, QString brickImageUrl, QString highlightedBrickImageUrl) :
    QWidget(parent)
    ,brickPixmap(brickImageUrl)
    ,highlightedBrickPixmap(highlightedBrickImageUrl)
{
    setHistory(history);
    this->length = historyWidth;

    int width = (brickPixmap.width()+HORIZONTAL_PADDING)*historyWidth;
    int height = (brickPixmap.height()+VERTICAL_PADDING)*historyHeight;

    setFixedSize(width, height);
}

void HistoryWidget::setHistory(int* history){
    this->history = history;
    update();
}

void HistoryWidget::paintEvent(QPaintEvent *){
    QPainter qpainter (this);

    for(int i=0;i<length;i++){
        int x = i*(brickPixmap.width()+HORIZONTAL_PADDING);
        int y = height() - brickPixmap.height();

        if(y<=0){
            qDebug() << "y is bad!";
        }

        int squares = history[i];

        while(squares > 0){

            QPixmap pixmap;

            if(squares == 1){
                pixmap = highlightedBrickPixmap;
            }
            else{
                pixmap = brickPixmap;
            }

            qpainter.drawPixmap(x, y, pixmap);

            y -= brickPixmap.height()+VERTICAL_PADDING;
            squares--;
        }
    }
}


