#include <QDebug>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>
#include <QTextCodec>
#include "worker.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);

    WorkerClass worker(&a);
    worker.send_reply();

    //return a.exec();
}
