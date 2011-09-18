
#include <QtGui>
#include <QtWebKit>
#include "WebWidget.h"
#include "abstractscreen.h"
#include "qdebug.h"
#include "useragentwebpage.h"

WebWidget::WebWidget(const QUrl& url) :
    webMask(":/images/images/main_screen_large_video_mask.png")
    ,keyboardButton(this)
{
    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    file.close();
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    view = new WebView(this);
    view->load(url);
    view->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
//    view->setPage(new UserAgentWebPage(this));

    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    locationEdit = new MyLineEdit();
    locationEdit->setParent(this);
    locationEdit->setStyleSheet("font-size: 18px");
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    goButton = new QPushButton("GO");
    connect(goButton, SIGNAL(pressed()), SLOT(changeLocation()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addWidget(locationEdit);
    toolBar->addWidget(goButton);
    toolBar->setMovable(false);

    /**
      * I'm not sure why there are so many nested QWidgets
      * here that must be set to the same size, but it's not
      * work refactoring right now.
      */
    QRect geometry(10,10,740, 540);

    QWidget* container = new QWidget();
    container->setFixedSize(geometry.size());;
    view->setParent(container);
    view->setFixedSize(geometry.size());
    keyboardButton.setParent(container);

    setCentralWidget(container);
    this->setGeometry(geometry);
    this->setAutoFillBackground(true);

    connect(view->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(onJavaScriptWindowObjectCleared()));
}
//! [3]

//! [4]
void WebWidget::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void WebWidget::changeLocation()
{

    QString txt = locationEdit->text();
    QUrl url;
//    QUrl url = txt;
    if (txt.contains(QString("http://www.")))
    {
        url = QUrl(txt);
    }
    else
    {
        if (txt.contains(QString("www.")))
        {
            url = QUrl(QString("http://")+txt);
        }
        else
        {
            url = QUrl(QString("http://www.")+txt);
        }
    }
    view->load(url);
    view->setFocus();
}
//! [4]

//! [6]
void WebWidget::finishLoading(bool)
{
    view->page()->mainFrame()->evaluateJavaScript(jQuery);
}
//! [6]

void WebWidget::SetUrl(const QUrl &url)
{
    view->load(url);
}
