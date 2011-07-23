#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>

class WebView : public QWebView
{
    Q_OBJECT
public:
    explicit WebView(QWidget *parent = 0);

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event);

private:
    QPoint lastTouchPoint;

signals:

public slots:

};

#endif // WEBVIEW_H
