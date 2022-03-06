#include "connection.h"

Connection::Connection(){}

void Connection::closeconnection(){ db.close(); }

bool Connection::createconnect(){
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test");
    db.setUserName("onskh");                //inserer nom de l'utilisateur
    db.setPassword("onskh");                //inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}
