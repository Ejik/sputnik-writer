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

    ui->lineEdit->setText(settings.value("Раздел").toString());
    ui->lineEdit_2->setText(settings.value("Рубрика").toString());
    ui->lineEdit_3->setText(settings.value("Ключевое").toString());
    ui->textEdit->setText(settings.value("Текст").toString());
    ui->lineEdit_4->setText(settings.value("Телефон").toString());
    ui->textEdit_2->setText(settings.value("ФИО").toString());
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.setValue("Раздел", ui->lineEdit->text());
    settings.setValue("Рубрика", ui->lineEdit_2->text());
    settings.setValue("Ключевое", ui->lineEdit_3->text());
    settings.setValue("Текст", ui->textEdit->toPlainText());
    settings.setValue("Телефон", ui->lineEdit_4->text());
    settings.setValue("ФИО", ui->textEdit_2->toPlainText());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("Sputnik writer"), tr("Публикация объявлений на сайт http://www.sputnik-cher.ru"));
}

void MainWindow::on_actionSubmit_triggered()
{

}
