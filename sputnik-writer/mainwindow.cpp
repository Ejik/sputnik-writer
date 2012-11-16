#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSettings"

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
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.setValue("Раздел", ui->lineEdit->text());
    settings.setValue("Рубрика", ui->lineEdit_2->text());
}
