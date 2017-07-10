#include "gameserver.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QHostInfo>
extern MainWindow * mainwindow;

GameServer::GameServer(QObject *parent):QTcpServer(parent)
{

}

GameServer::~GameServer()
{
}

void GameServer::startServer(int portId)
{
    QString msg;
    if (isListening()){
        msg = "Server started already!";
    }else if(this->listen(QHostAddress::AnyIPv4, portId))
    {

        msg = "Server started!";
        serverDB = new ServerDB();
        serverDB->connect_db();
        qDebug() << msg;

    }else{
        msg = "Cannot start the server!";
    }
    mainwindow->status_message(msg);
}



void GameServer::clientdisconnect()
{
    for (auto client : client_list){
        client->disconnectFromHost();
    }
}

void GameServer::client_login(QList<QByteArray> &data)
{
    QString user_name = QTextCodec::codecForMib(106)->toUnicode(data[0]);
    QString password = QTextCodec::codecForMib(106)->toUnicode(data[1]);
    if (serverDB->find_user(user_name, password)){

    }
}
void GameServer::readyRead()
{
    // this happens on the main thread!
    QTcpSocket *client = (QTcpSocket*)sender();

    QByteArray rawData = client->readAll();
    QList<QByteArray> dataPackage = rawData.split('%');

    qDebug() << client->socketDescriptor() <<rawData ;

    if(dataPackage[0] == "Login"){
        qDebug()<< "Login";
        dataPackage.removeFirst();
        client_login(dataPackage);
    }else if(dataPackage[0]=="Msg")
    {
        //game->chat->messageReceived(dataPackage[1]);

    }
    else{
        qDebug() << rawData;

    }
    client->write("message got");
}

void GameServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();
    mainwindow->status_message("Client disconnected: " + client->peerAddress().toString());


}







void GameServer::incomingConnection(qintptr socketfd)
{
    QTcpSocket * client = new QTcpSocket();

    QString msg;
    if(!client->setSocketDescriptor(socketfd))
    {
        msg = "connection error";
    }
    client_list.append(client);
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << "Connection from " << client->socketDescriptor();
    msg = "Connection from "+ QString::number(client->socketDescriptor());
    qDebug() << msg;
    mainwindow->status_message(msg);


}



