#include "historywidget.h"
#include <QPainter>
#include <QDebug>

static int VERTICAL_PADDING = 1;
static int HORIZONTAL_PADDING = 3;
static int SQUARE_WIDTH = 8;
static int SQUARE_HEIGHT = 4;

HistoryWidget::HistoryWidget(QWidget *parent, int history[], int historyWidth, int historyHeight) :
    QWidget(parent)
{
    this->history = history;
    this->length = historyWidth;

    int width = (SQUARE_WIDTH+HORIZONTAL_PADDING)*historyWidth;
    int height = (SQUARE_HEIGHT+VERTICAL_PADDING)*historyHeight;

    setFixedSize(width, height);
}

void HistoryWidget::paintEvent(QPaintEvent *){
    QPainter qpainter (this);

    for(int i=0;i<length;i++){
        int x = i*(SQUARE_WIDTH+HORIZONTAL_PADDING);
        int y = height() - SQUARE_HEIGHT;

        if(y<=0){
            qDebug() << "y is bad!";
        }

        QColor color(255,255,255, 50);
        int squares = history[i];

        while(squares > 0){

            qpainter.fillRect(x,y, SQUARE_WIDTH, SQUARE_HEIGHT, color);

            y -= SQUARE_HEIGHT+VERTICAL_PADDING;
            color.setAlpha(color.alpha()+6);

            squares--;
        }
    }
}
