#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include <QtGui>
#include "abstractscreen.h"
#include "webview.h"
#include "keyboardscreen.h"
#include "screens.h"

static const QString HOME_URL = "http://max-mobility.com/launchpad";

namespace Ui {
    class WebWidget;
}

class WebWidget : public QMainWindow
{
    Q_OBJECT

public:
    WebWidget(QString url);
    void SetUrl(const QUrl& url);

private:
    QString jQuery;
    QWebView *view;
    QLineEdit *locationEdit;
//    QPushButton *goButton;
    QAction *rotateAction;

    QPixmap webMask;

    InvisibleButton keyboardButton;

protected slots:

    void adjustLocation();
    void changeLocation();
    void finishLoading(bool);

public slots:
    void changeLocation(QString);
};

class MyLineEdit : public QLineEdit{

    Q_OBJECT

    void mousePressEvent(QMouseEvent* event){
        KeyboardScreen* keyboardScreen = new KeyboardScreen(text(), this);

        connect(keyboardScreen, SIGNAL(enterPressed(QString)), this, SLOT(enterPressed(QString)));

        Screens::show(keyboardScreen);
        QLineEdit::mousePressEvent(event);
    }

public:
    WebWidget* webWidget;

signals:
    void addressEntered(QString url);

private slots:
    void enterPressed(QString url){
        emit addressEntered(url);
    }


};

#endif // WEBWIDGET_H
