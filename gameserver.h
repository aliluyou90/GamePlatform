#ifndef GAMESERVER_H
#define GAMESERVER_H
#include <QObject>
#include <QTcpServer>


class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent =0);
    ~GameServer();
    bool startServer(int portId);
    void clientdisconnect();
private slots:
    void readyRead();
    void disconnected();
protected:
    void incomingConnection(qintptr socketfd);

private:
    QTcpSocket* client;
};


#endif // GAMESERVER_H