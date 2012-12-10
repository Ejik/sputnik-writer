#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkCookie>

#include "httprequestclass.h"


HttpRequestClass::HttpRequestClass(QObject *parent) :
    QObject(parent)
{
}


QNetworkReply* HttpRequestClass::submit(QMap<QString, QString> params)
{
    QList<QNetworkCookie> cookies;

    cookies.append(QNetworkCookie("lang", "1"));
    cookies.append(QNetworkCookie("sid", "none"));

    QByteArray arr;
    arr.append("a=" + params.value("Контакты"));
    arr.append("c=" + params.value("Рубрика"));
    arr.append("k=" + params.value("Ключевое"));
    arr.append("p=" + params.value("Телефон"));
    arr.append("r=" + params.value("Раздел"));
    arr.append("t=" + params.value("Текст"));

    qDebug() << arr;

    //request_.setUrl(QUrl("http://www.sputnik-cher.ru/add/send/index.asp"));
    request_.setUrl(QUrl("http://www.sputnik-cher.ru/add/"));
    request_.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    reply_ = manager_.post(request_, arr);

    return reply_;
}

