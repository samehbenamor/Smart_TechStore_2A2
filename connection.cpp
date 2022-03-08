#include "connection.h"

Connection::Connection()
{

}



bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("lunatics");
db.setUserName("ali");//inserer nom de l'utilisateur
db.setPassword("ali");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
