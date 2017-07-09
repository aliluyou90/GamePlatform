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


void MainWindow::on_start_pushButton_clicked()
{
    QString str;
    int portId = ui->port_lineEdit->text().toInt();
    if (server->isListening()){
        str = "Server have been started";
    }else{
        if(portId >=1000 && portId <=2000){


            if(server->startServer(portId)){
                str = "Server Started! Port: "+ ui->port_lineEdit->text();
            }else {
                str = "Error!";
            }

        }else{
            str = "Please use another port.";
        }
    }

    ui->status_textBrowser->append(str);
}

void MainWindow::on_shutDown_pushButton_clicked()
{
    QString str ;
    if (server->isListening()){
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


