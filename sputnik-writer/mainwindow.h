#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionExit_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    void read_settings();
    void write_settings();

};

#endif // MAINWINDOW_H