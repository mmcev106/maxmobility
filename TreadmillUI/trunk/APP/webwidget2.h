#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include <QWebView>
#include <QVariant>

class WebWidget : public QWebView
{
    Q_OBJECT

public:
    WebWidget(QWidget* parent);

public slots:
    QVariant onTextFieldFocused();
    void onJavaScriptWindowObjectCleared();
};

#endif // WEBWIDGET_H
