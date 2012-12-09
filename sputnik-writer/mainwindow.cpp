#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include "QSettings"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fill_combos();

    read_settings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fill_combos()
{
    ui->combo_section->clear();
    ui->combo_heading->clear();

    ui->combo_section->addItem(tr("Недвижимость"), QVariant(0));
    ui->combo_section->addItem(tr("Строительство"), QVariant(1));
    ui->combo_section->addItem(tr("Интерьер"), QVariant(2));
    ui->combo_section->addItem(tr("Животные, растения"), QVariant(3));
    ui->combo_section->addItem(tr("Работа"), QVariant(4));

    ui->combo_heading->addItem(tr("Предлагаю работу"), QVariant(301));
    ui->combo_heading->addItem(tr("Ищу работу"), QVariant(305));


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

    int cur_sec_idx = ui->combo_section->currentIndex();
    int cur_head_idx = ui->combo_heading->currentIndex();

    QMap<QString, QString> params;
    params.insert("Раздел", ui->combo_section->itemData(cur_sec_idx).toString());
    params.insert("Рубрика", ui->combo_heading->itemData(cur_head_idx).toString());
    params.insert("Ключевое", ui->lineEdit_3->text());
    params.insert("Текст", ui->textEdit->toPlainText());
    params.insert("Телефон", ui->lineEdit_4->text());
    params.insert("Контакты", ui->textEdit_2->toPlainText());

    QString err = submit(params);
    qDebug() << err;
}

QString MainWindow::submit(QMap<QString, QString> params)
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

    request_.setUrl(QUrl("http://www.sputnik-cher.ru/add/send/index.asp"));
    request_.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    reply_ = manager_.post(request_, arr);
    connect(reply_, SIGNAL(readyRead()), this, SLOT(DataReady()));
    connect(reply_, SIGNAL(finished()), this, SLOT(ReplyFinished()));

    return "OK";
}

void MainWindow::DataReady()
{
    QByteArray data = reply_->readAll();
    qDebug() << "reply " << data.size() << " bytes";

    QFile file(QDir::currentPath() + "/test.html");
    file.open(QIODevice::Append);
    file.write(data);
    file.close();

}

void MainWindow::ReplyFinished()
{
    qDebug() << "finished.";
}

void MainWindow::on_combo_section_currentIndexChanged(int index)
{
    QString str;
    ui->textedit_debug->setText("Section index = " + str.setNum(index) + " Data = " + ui->combo_section->itemData(index).toString());
}

void MainWindow::on_combo_heading_currentIndexChanged(int index)
{
    QString str;
    ui->textedit_debug->setText("Heading index = " + str.setNum(index) + " Data = " + ui->combo_heading->itemData(index).toString());
}
