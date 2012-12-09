#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void DataReady();
    void ReplyFinished();

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionSubmit_triggered();

    void on_combo_section_currentIndexChanged(int index);

    void on_combo_heading_currentIndexChanged(int index);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager_;
    QNetworkRequest request_;
    QNetworkReply *reply_;


    void read_settings();
    void write_settings();
    QString submit(QMap<QString, QString> params);
    void fill_combos();

};

#endif // MAINWINDOW_H
