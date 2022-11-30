#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <winsock2.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimer();

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_pushButton_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::MainWindow *ui;
    SOCKET s=0;
    QTimer tmr;
};
#endif // MAINWINDOW_H
