#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <qtextstream.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    Connection c;
    bool test =c.createconnect();
    QApplication a(argc, argv);
    MainWindow w;

    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("base de donneé overte"),QObject::tr("Connection etabit avec succès"));
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("base de doneé fermée"),QObject::tr("Connection échouer"));
    w.show();

    return a.exec();
}
