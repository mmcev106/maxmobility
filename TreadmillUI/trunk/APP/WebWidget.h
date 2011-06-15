#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include <QtGui>
#include <QWebView>
#include "abstractscreen.h"

const QUrl HOME_URL = QUrl("http://www.google.com");

namespace Ui {
    class WebWidget;
}

class WebWidget : public QMainWindow
{
    Q_OBJECT

public:
    WebWidget(const QUrl& url);
    void SetUrl(const QUrl& url);

private:
    QString jQuery;
    QWebView *view;
    QLineEdit *locationEdit;
    QAction *rotateAction;

    QPixmap webMask;

protected slots:

    void adjustLocation();
    void changeLocation();
    void finishLoading(bool);
};

#endif // WEBWIDGET_H
