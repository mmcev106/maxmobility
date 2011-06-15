#ifndef WEBWIDGET_H
#define WEBWIDGET_H


#include <QtGui>
#include <QWidget>
#include "abstractscreen.h"

class QWebView;
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

namespace Ui {
    class WebWidget;
}

class WebWidget : public QMainWindow
{
    Q_OBJECT

public:
    WebWidget(const QUrl& url);

private:
    QString jQuery;
    QWebView *view;
    QLineEdit *locationEdit;
    QAction *rotateAction;
    int progress;

    QPixmap webMask;

protected slots:

    void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);
};

#endif // WEBWIDGET_H
