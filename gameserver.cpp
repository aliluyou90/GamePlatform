#include "gameserver.h"
#include <QDebug>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QHostInfo>


GameServer::GameServer(QObject *parent):QTcpServer(parent)
{

}

GameServer::~GameServer()
{
}

bool GameServer::startServer(int portId)
{
    if(this->listen(QHostAddress::AnyIPv4, portId))
    {
        qDebug() << "server started";
        return true;
    }
    return false;
}



void GameServer::clientdisconnect()
{
    client->disconnectFromHost();
}


void GameServer::readyRead()
{


}

void GameServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();



}







void GameServer::incomingConnection(qintptr socketfd)
{
    client = new QTcpSocket();
    if(!client->setSocketDescriptor(socketfd))
    {
        qDebug()<< "connection error";
        return;
    }
    qDebug() << "Connection from " << client->socketDescriptor();



}

