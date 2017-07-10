#ifndef GAMESERVER_H
#define GAMESERVER_H
#include <QObject>
#include <QTcpServer>
#include "serverdb.h"

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent =0);
    ~GameServer();
    void startServer(int portId);
    void clientdisconnect();
private slots:
    void readyRead();
    void disconnected();
protected:
    void incomingConnection(qintptr socketfd);

private:
    QList<QTcpSocket*> client_list;
    ServerDB * serverDB;
    // methods
    void client_login(QList<QByteArray> &data);
};


#endif // GAMESERVER_H
