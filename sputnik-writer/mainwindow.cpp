#include <QDebug>
#include <QMessageBox>
#include "QSettings"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    read_settings();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::fill_combos()
{
    ui->combo_section->addItem("Недвижимость", QVariant(0));
    ui->combo_section->addItem("Строительство", QVariant(1));
    ui->combo_section->addItem("Интерьер", QVariant(2));
    ui->combo_section->addItem("Животные, растения", QVariant(3));
    ui->combo_section->addItem("Работа", QVariant(4));

    ui->combo_heading->addItem("Предлагаю работу", QVariant(301));
    ui->combo_heading->addItem("Ищу работу", QVariant(305));


}

void MainWindow::on_actionExit_triggered()
{
    write_settings();

    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    write_settings();
}

void MainWindow::read_settings()
{
    QCoreApplication::setOrganizationName("Autocontrolsystems");
    QCoreApplication::setOrganizationDomain("autocontrolsystems.com");
    QCoreApplication::setApplicationName("sputnik-writer");

    QSettings settings;

    ui->combo_section->setCurrentIndex(settings.value("Раздел").toInt());
    ui->combo_heading->setCurrentIndex(settings.value("Рубрика").toInt());
    ui->lineEdit_3->setText(settings.value("Ключевое").toString());
    ui->textEdit->setText(settings.value("Текст").toString());
    ui->lineEdit_4->setText(settings.value("Телефон").toString());
    ui->textEdit_2->setText(settings.value("Контакты").toString());
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.setValue("Раздел", ui->combo_section->currentIndex());
    settings.setValue("Рубрика", ui->combo_heading->currentIndex());
    settings.setValue("Ключевое", ui->lineEdit_3->text());
    settings.setValue("Текст", ui->textEdit->toPlainText());
    settings.setValue("Телефон", ui->lineEdit_4->text());
    settings.setValue("Контакты", ui->textEdit_2->toPlainText());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("Sputnik writer"), tr("Публикация объявлений на сайт http://www.sputnik-cher.ru"));
}

void MainWindow::on_actionSubmit_triggered()
{

    int cur_sec_idx = ui->combo_heading->currentIndex();
    int cur_head_idx = ui->combo_heading->currentIndex();

    QMap<QString, QVariant> params;
    params.insert("Раздел", ui->combo_section->itemData(cur_sec_idx).toInt());
    params.insert("Рубрика", ui->combo_heading->itemData(cur_head_idx).toInt());
    params.insert("Ключевое", ui->lineEdit_3->text());
    params.insert("Текст", ui->textEdit->toPlainText());
    params.insert("Телефон", ui->lineEdit_4->text());
    params.insert("Контакты", ui->textEdit_2->toPlainText());

    QString err = submit(params);
    qDebug() << err;
}

QString MainWindow::submit(QMap<QString, QVariant> params)
{
    QList<QNetworkCookie> cookies;
    cookies.append(QNetworkCookie("rub", params.value("Раздел").toInt()));
    cookies.append(QNetworkCookie("cat", params.value("Рубрика")));
    cookies.append(QNetworkCookie("key", params.value("Ключевое")));
    cookies.append(QNetworkCookie("txt", params.value("Текст")));
    cookies.append(QNetworkCookie("phone", params.value("Телефон")));
    cookies.append(QNetworkCookie("contacts", params.value("Контакты")));

    request.setUrl(QUrl("http://www.sputnik-cher.ru/add/"));
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    reply = manager.post(request, "user=lol&pass=123");
    connect(reply, SIGNAL(readyRead()), this, SLOT(DataReady()));
    connect(reply, SIGNAL(finished()), this, SLOT(ReplyFinished()));

    return "OK";
}

void MainWindow::DataReady()
{
    QByteArray data = reply->readAll();
    qDebug() << "reply " << data.size() << " bytes";
    qDebug() << data;
}

void MainWindow::ReplyFinished()
{

    qDebug() << "finished.";

}
