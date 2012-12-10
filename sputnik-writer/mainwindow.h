#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>
#include <QMap>
#include "..\common\httprequestclass.h"

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

    void read_settings();
    void write_settings();    
    void fill_combos();
    QString get_combo_userdata_by_index(QComboBox *combo);
    int get_combo_index_by_userdata(QComboBox *combo, int data);
    HttpRequestClass request_;
    QNetworkReply *reply_;

};

#endif // MAINWINDOW_H
