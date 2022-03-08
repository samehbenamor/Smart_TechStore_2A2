#include "commandes.h"
#include <QDebug>
#include <QMessageBox>
Commandes::Commandes(int idc,QString datec,QString localisation,int etatc,int id_c)
{
    this->id_co=idc;
    this->datec=datec;
    this->localisation=localisation;
    this->etatc=etatc;
    this->id_c=id_c;
}
bool Commandes::AjouterCommandes()
{
    QSqlQuery query;
    QString id = QString::number(id_co);
    query.prepare("insert into commande (id_co,datec,localisation,etatc)" "values (:id_co, :datec,:localisation,:etatc)");
    query.bindValue(":id_co",id);
    query.bindValue(":datec",datec);
    query.bindValue(":localisation",localisation);
    query.bindValue(":etatc",etatc);
    return query.exec();
}
bool Commandes::SupprimerCommandes(int id)
{
    QSqlQuery query;
    QString Id = QString::number(id);
    query.prepare("Delete from commande where id_co=:id_co");
    query.bindValue(":id_co",Id);
    return query.exec();
}
QSqlQueryModel * Commandes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from commande");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date commande"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Id du client"));
    return  model;
}
bool Commandes::rechercherClients(int i)
{
    bool k=false;
    QSqlQuery query;
    QString Id = QString::number(i);
    query.prepare("select * from client where id_c=:id_c");
    query.bindValue(":id_c",Id);
    query.exec();
    while (query.next()) {
    k=query.value(0).toBool();
    }

    return  k;
}
QSqlQuery Commandes::rechercherCommandes(int i)
{

    QSqlQuery query;
    QString Id = QString::number(i);
    query.prepare("select * from commande where id_co=:id_co");
    query.bindValue(":id_co",Id);
    query.exec();
    return   query;

}

bool Commandes::modifierCommandes(int id,QString date,QString loc,int etat,int idclient){
        QSqlQuery query;

QString Id = QString::number(id);
query.prepare(" UPDATE commande SET datec=:datec,localisation=:localisation,etatc=:etatc,id_c=:id_c WHERE id_co=:id_co");
       query.bindValue(":id_co",Id);
       query.bindValue(":etatc",etat);
       query.bindValue(":datec",date);
       query.bindValue(":localisation",loc);
       query.bindValue(":id_c",idclient);
       return  query.exec();

}
