#include "webview.h"

#include <QDebug>
#include <QMouseEvent>
#include <QWebFrame>

WebView::WebView(QWidget *parent) :
    QWebView(parent)
{
}

void WebView::mouseMoveEvent(QMouseEvent *event){

    if(event->buttons() == Qt::LeftButton){

        QPoint currentTouchPoint = event->pos();

        int dx = lastTouchPoint.x() - currentTouchPoint.x();
        int dy = lastTouchPoint.y() - currentTouchPoint.y();

        page()->mainFrame()->scroll(dx, dy);

        lastTouchPoint =  event->pos();
    }
    else{
        QWebView::mouseMoveEvent(event);
    }
}

void WebView::mousePressEvent(QMouseEvent *event){

    lastTouchPoint =  event->pos();
    QWebView::mousePressEvent(event);
}
