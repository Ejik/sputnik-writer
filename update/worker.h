#ifndef WORKER_H
#define WORKER_H

#include <QtCore>
#include <QObject>
#include <QNetworkReply>

class WorkerClass : public QObject
{
    Q_OBJECT
public:
    explicit WorkerClass(QCoreApplication *a, QObject *parent = 0 );
    void send_reply();

private:
    void read_settings();

    QNetworkReply *reply_;
    QCoreApplication *a_;

signals:
    
public slots:    
    void DataReady();
    void ReplyFinished();

};

#endif // WORKER_H
