#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include "invisiblebutton.h"
#include "keyboardscreen.h"

class WebView : public QWebView
{
    Q_OBJECT
public:
    explicit WebView(QWidget *parent = 0);

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event);
    void mouseReleaseEvent( QMouseEvent * event);

private:
    QPoint lastPressPoint;
    QPoint lastTouchPoint;

    int unusedDx;
    int unusedDy;
    long lastScrollTime;

signals:

public slots:
    void onTextFieldClicked(QString text);
    void onLoadFinished(bool ok);

};

#endif // WEBVIEW_H
