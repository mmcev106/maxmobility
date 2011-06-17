#include "useragentwebpage.h"

UserAgentWebPage::UserAgentWebPage(QWidget *parent) :
    QWebPage(parent)
{
}

QString UserAgentWebPage::userAgentForUrl(const QUrl &url ) const {
    return QString("Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_7; en-us) AppleWebKit/533.21.1 (KHTML, like Gecko) Version/5.0.5 Safari/533.21.1");
}
