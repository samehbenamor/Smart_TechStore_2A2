#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "employees.h"
#include "reparation.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Gestion_emp w;
    Connection c;

    bool test=c.createconnect();                                                                                            //Etablir connection
    MainWindow t;
    if(test)
    {t.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
