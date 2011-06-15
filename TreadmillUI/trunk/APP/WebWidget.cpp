
#include <QtGui>
#include <QtWebKit>
#include "WebWidget.h"

//! [1]

WebWidget::WebWidget(const QUrl& url)
{
    progress = 0;

    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    file.close();
//! [1]

    QNetworkProxyFactory::setUseSystemConfiguration(true);

//! [2]
    view = new QWebView(this);
    view->load(url);
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
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
//! [2]

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);
    this->setGeometry(130,95,725,570);

    setCentralWidget(view);
    setUnifiedTitleAndToolBarOnMac(true);
}
//! [3]

//! [4]
void WebWidget::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void WebWidget::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}
//! [4]

//! [5]
void WebWidget::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void WebWidget::setProgress(int p)
{
    progress = p;
    adjustTitle();
}
//! [5]

//! [6]
void WebWidget::finishLoading(bool)
{
    progress = 100;
    adjustTitle();
    view->page()->mainFrame()->evaluateJavaScript(jQuery);
}
//! [6]

