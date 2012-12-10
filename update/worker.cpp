#include <QDebug>
#include <QFile>
#include <QSettings>
#include "..\common\httprequestclass.h"
#include "worker.h"

WorkerClass::WorkerClass(QCoreApplication *a, QObject *parent) :
    QObject(parent)
{
    a_ = a;
}

void WorkerClass::send_reply()
{
    read_settings();

    QSettings settings;

    QMap<QString, QString> params;
    params.insert("Раздел", settings.value("Раздел").toString());
    params.insert("Рубрика", settings.value("Рубрика").toString());
    params.insert("Ключевое", settings.value("Ключевое").toString());
    params.insert("Текст", settings.value("Текст").toString());
    params.insert("Телефон", settings.value("Телефон").toString());
    params.insert("Контакты", settings.value("Контакты").toString());

    HttpRequestClass request;
    reply_ = request.submit(params);
    connect(reply_, SIGNAL(readyRead()), this, SLOT(DataReady()));
    connect(reply_, SIGNAL(finished()), this, SLOT(ReplyFinished()));
}

void WorkerClass::read_settings()
{
    QCoreApplication::setOrganizationName("Autocontrolsystems");
    QCoreApplication::setOrganizationDomain("autocontrolsystems.com");
    QCoreApplication::setApplicationName("sputnik-writer");

//    ui->combo_section->setCurrentIndex(settings.value("Раздел").toInt());
//    ui->combo_heading->setCurrentIndex(settings.value("Рубрика").toInt());
//    ui->lineEdit_3->setText(settings.value("Ключевое").toString());
//    ui->textEdit->setText(settings.value("Текст").toString());
//    ui->lineEdit_4->setText(settings.value("Телефон").toString());
//    ui->textEdit_2->setText(settings.value("Контакты").toString());
}

void WorkerClass::DataReady()
{
    QByteArray data = reply_->readAll();
    qDebug() << "reply " << data.size() << " bytes";

    QFile file(QDir::currentPath() + "/test.html");
    file.open(QIODevice::Append);
    file.write(data);
    file.close();

}

void WorkerClass::ReplyFinished()
{
    qDebug() << "finished.";
}
