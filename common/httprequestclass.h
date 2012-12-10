#ifndef HTTPREQUESTCLASS_H
#define HTTPREQUESTCLASS_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QNetworkReply>

class HttpRequestClass : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequestClass(QObject *parent = 0);
    QNetworkReply *reply() { return reply_; }


    QNetworkReply *submit(QMap<QString, QString> params);

private:

    QNetworkAccessManager manager_;
    QNetworkRequest request_;
    QNetworkReply *reply_;

signals:
    
public slots:
    
};

#endif // HTTPREQUESTCLASS_H
