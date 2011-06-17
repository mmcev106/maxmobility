
#include <QtGui>
#include <QtWebKit>
#include "WebWidget.h"
#include "abstractscreen.h"
#include "qdebug.h"
#include "useragentwebpage.h"

WebWidget::WebWidget(const QUrl& url) :
        webMask(":/images/images/main_screen_large_video_mask.png")
{
    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    file.close();
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    view = new QWebView(this);
    view->load(url);
    view->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    view->setPage(new UserAgentWebPage(this));

    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addWidget(locationEdit);
    toolBar->setMovable(false);

    setCentralWidget(view);
    this->setGeometry(140,110,740,545);
    this->setAutoFillBackground(true);
//    this->setMask(webMask.mask());
//    this->clearMask();
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
    if (txt.contains(QString("http://www.")))
        url = QUrl(txt);
    else if (txt.contains(QString("www.")))
        url = QUrl("http://"+txt);
    else
        url = QUrl("http://www."+txt);
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

