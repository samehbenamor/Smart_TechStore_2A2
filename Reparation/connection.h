#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
    QSqlDatabase db;

public:
    Connection();
    void closeconnection();
    bool createconnect();
};

#endif // CONNECTION_H
