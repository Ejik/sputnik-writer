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

    int current_index = get_combo_index_by_userdata(ui->combo_section, settings.value("Раздел").toInt());
    if (current_index != -1)
        ui->combo_section->setCurrentIndex(current_index);

    current_index = get_combo_index_by_userdata(ui->combo_heading, settings.value("Рубрика").toInt());
    if (current_index != -1)
        ui->combo_heading->setCurrentIndex(current_index);

    ui->lineEdit_3->setText(settings.value("Ключевое").toString());
    ui->textEdit->setText(settings.value("Текст").toString());
    ui->lineEdit_4->setText(settings.value("Телефон").toString());
    ui->textEdit_2->setText(settings.value("Контакты").toString());
}

void MainWindow::write_settings()
{
    QSettings settings;

    settings.setValue("Раздел", get_combo_userdata_by_index(ui->combo_section));
    settings.setValue("Рубрика",get_combo_userdata_by_index(ui->combo_heading));
    settings.setValue("Ключевое", ui->lineEdit_3->text());
    settings.setValue("Текст", ui->textEdit->toPlainText());
    settings.setValue("Телефон", ui->lineEdit_4->text());
    settings.setValue("Контакты", ui->textEdit_2->toPlainText());
}

QString MainWindow::get_combo_userdata_by_index(QComboBox *combo)
{
    int cur_idx = combo->currentIndex();
    return combo->itemData(cur_idx).toString();
}

int MainWindow::get_combo_index_by_userdata(QComboBox *combo, int data)
{
    int i = 0;
    while (i < combo->count()) {
        int current_data = combo->itemData(i).toInt();
        if (current_data == data)
            return i;
        i++;
    }
    return -1;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("Sputnik writer"), tr("Публикация объявлений на сайт http://www.sputnik-cher.ru"));
}

void MainWindow::on_actionSubmit_triggered()
{    
    QMap<QString, QString> params;
    params.insert("Раздел", get_combo_userdata_by_index(ui->combo_section));
    params.insert("Рубрика", get_combo_userdata_by_index(ui->combo_heading));

    params.insert("Ключевое", ui->lineEdit_3->text().toUtf8());
    params.insert("Текст", ui->textEdit->toPlainText().toUtf8());
    params.insert("Телефон", ui->lineEdit_4->text().toUtf8());
    params.insert("Контакты", ui->textEdit_2->toPlainText().toUtf8());

    reply_ = request_.submit(params);
    connect(reply_, SIGNAL(readyRead()), this, SLOT(DataReady()));
    connect(reply_, SIGNAL(finished()), this, SLOT(ReplyFinished()));

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
