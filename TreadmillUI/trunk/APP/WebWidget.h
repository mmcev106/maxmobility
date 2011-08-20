#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include <QtGui>
#include "abstractscreen.h"
#include "webview.h"
#include "keyboardscreen.h"
#include "screens.h"

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
    QPushButton *goButton;
    QAction *rotateAction;

    QPixmap webMask;

    InvisibleButton keyboardButton;

protected slots:

    void adjustLocation();
    void changeLocation();
    void finishLoading(bool);
};

class MyLineEdit : public QLineEdit{
    void mousePressEvent(QMouseEvent* event){
        Screens::show(new KeyboardScreen(text(), this));
        QLineEdit::mousePressEvent(event);
    }
};

#endif // WEBWIDGET_H
