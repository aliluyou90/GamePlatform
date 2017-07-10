#include "serverdb.h"
#include "mainwindow.h"
extern MainWindow * mainwindow;
ServerDB::ServerDB()
{
    db = new QSqlDatabase();
}

void ServerDB::connect_db()
{
    *db = QSqlDatabase::addDatabase("QODBC");
    db->setHostName("LOCALHOST\\SQLEXPRESS");
    db->setDatabaseName("mydsn64");
    if(db->open()){
        qDebug() << "database opened!";

        mainwindow->status_message("Connected to database");
    }else{
        qDebug() << db->lastError().text();
        mainwindow->status_message(db->lastError().text());
    }
}

bool ServerDB::find_user(QString user_name, QString password)
{
    auto queryString = QString("SELECT [password],[ID] from [loginInfo] WHERE [userName] = '%1'").arg(user_name);
    QSqlQuery query(queryString);
    if(query.next()){
        qDebug() << query.value(0).toString();
            if(password == query.value(0).toString().trimmed()){

                mainwindow->status_message("User Login");
                return true;
            }else{
                mainwindow->status_message("Wrong Password");
            }

    }else{
        mainwindow->status_message("Invalid ID");
    }
    return false;
}
