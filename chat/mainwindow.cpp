#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ws2tcpip.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    connect(&tmr, SIGNAL(timeout()), SLOT(onTimer()));
    tmr.start(50);
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::onTimer()
{
    if(s==0)
        return;

    char msg[256];
    int err=recv(s, msg, 256, 0);
    if(err==0)
    {
        on_action_4_triggered();
        return;
    }
    if(err<0)
    {
        int e=WSAGetLastError();
        if (e==WSAETIMEDOUT)
            return;

        ui->textEdit->append("Fatal error!");
        return;
    }

    ui->textEdit->append(QString::fromUtf8(msg, err));
}
//------------------------------------------------------------------------------
void MainWindow::on_action_2_triggered()
{
    s=socket(AF_INET, SOCK_STREAM, 0);
    if (s==INVALID_SOCKET)
    {
        ui->textEdit->append("Unable to connect");
        return;
    }

    char* hostname = ui->lineEdit->text().toLatin1().data();        // IP-адрес или имя удаленного узла
    char* port = ui->spinBox->text().toLatin1().data();             // Порт удаленного узла в виде строки
    int err;
    sockaddr_in addr;
    struct addrinfo *result = NULL;
    err = getaddrinfo(hostname, port, NULL, &result);
    if(err != 0)
    {
        ui->textEdit->append("Unable to find adress");
        closesocket(s);
        s=0;
        return;
        /* Ошибка определения имени сервера, result использовать нельзя */
    }
    else
    {
        memcpy(&addr, result->ai_addr, sizeof(addr));
    }
    freeaddrinfo(result);

    err=::connect(s, (sockaddr*) &addr, sizeof (addr));
    if (err<0)
    {
        ui->textEdit->append("Unable to connect");
        closesocket(s);
        s=0;
        return;
    }

    int timeout = 20;                                               // таймаут в миллисекундах
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO,
        (char*)&timeout, sizeof(timeout));

    ui->textEdit->append("Connected!");
}
//------------------------------------------------------------------------------
void MainWindow::on_action_4_triggered()
{
    ui->textEdit->append("Socket closed");
    closesocket(s);
    s=0;
}
//------------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    if (s==0)
        return;

    QByteArray msg=ui->lineEdit_2->text().toUtf8();
    send(s, msg.data(), msg.size(), 0);

    ui->lineEdit_2->clear();
}
//------------------------------------------------------------------------------
void MainWindow::on_lineEdit_2_returnPressed()
{
    on_pushButton_clicked();
}
