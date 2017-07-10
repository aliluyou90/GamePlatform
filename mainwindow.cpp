#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    server = new GameServer();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::status_message(QString msg)
{
    ui->status_textBrowser->append(msg);
}


void MainWindow::on_start_pushButton_clicked()
{

    int portId = ui->port_lineEdit->text().toInt();
    server->startServer(portId);
}

void MainWindow::on_shutDown_pushButton_clicked()
{
    QString str ;
    if (server->isListening()){
        server->clientdisconnect();
        server->close();
        str = "Server Closed.";
    }else{
        str = "Server is not listening";
    }

    ui->status_textBrowser->append(str);

}

void MainWindow::on_exit_pushButton_clicked()
{

    this->close();
}


