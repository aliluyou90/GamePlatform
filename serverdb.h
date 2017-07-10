#ifndef SERVERDB_H
#define SERVERDB_H
#include <QtSql>

class ServerDB
{
    QSqlDatabase * db;
public:
    ServerDB();
    void connect_db();
    bool find_user(QString user_name, QString password);
};

#endif // SERVERDB_H
