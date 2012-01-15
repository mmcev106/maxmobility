#ifndef USERAGENTWEBPAGE_H
#define USERAGENTWEBPAGE_H

#include <QWebPage>

class UserAgentWebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit UserAgentWebPage(QWidget *parent = 0);

protected:
    QString userAgentForUrl(const QUrl &url ) const;

signals:

public slots:

};

#endif // USERAGENTWEBPAGE_H
