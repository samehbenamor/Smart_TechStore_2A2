#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;
db.setDatabaseName("testv2");
db.setUserName("yassine");
db.setPassword("0000");

if (db.open()) test=true;
return  test;
}
void Connection::closeConnection(){db.close();}
