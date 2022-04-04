#include "commandes.h"
#include <QDebug>
#include <QMessageBox>
Commandes::Commandes(int idc,QString datec,QString localisation,int etatc,int id_c,QString ville)
{
    this->id_co=idc;
    this->datec=datec;
    this->localisation=localisation;
    this->etatc=etatc;
    this->id_c=id_c;
    this->ville=ville;
}
bool Commandes::AjouterCommandes()
{
    QSqlQuery query;
    QString id = QString::number(id_co);
    query.prepare("insert into commande (id_co,datec,localisation,etatc,id_c,ville)" "values (:id_co, :datec,:localisation,:etatc,:id_c,:ville)");
    query.bindValue(":id_co",id);
    query.bindValue(":datec",datec);
    query.bindValue(":localisation",localisation);
    query.bindValue(":etatc",etatc);
    query.bindValue(":id_c",id_c);
    query.bindValue(":ville",ville);
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
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Id client"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Ville"));
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
QSqlQueryModel * Commandes::StatsCommandes(int type){
    QSqlQueryModel * model=new QSqlQueryModel();
    if(type==1)
    {
    model->setQuery("select id_c,(count(id_c)*100/ (select count(*)from commande)) as pourcentage from commande group by id_c");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID CLIENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("%"));
    }
    else if(type==2)
    {
    model->setQuery("select id_pr,(count(id_pr)*100/ (select count(*)from contenir)) as pourcentage from contenir group by id_pr");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID PRODUIT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("%"));
    }
    else if(type==3)
    {
        model->setQuery("select ville,(count(ville)*100/ (select count(*)from commande)) as pourcentage from commande group by ville");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("VILLE"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("%"));
    }
    return model;
}
QSqlQueryModel * Commandes::Recherche(int k,QString type)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery query;
if(k==1)
{
        int id_co= type.toInt();
        QString Id = QString::number(id_co);
        query.prepare("select * from commande where id_co=:id_co");
        query.bindValue(":id_co",Id);
        query.exec();
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date commande"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Id du client"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Ville"));
}
else if (k==2)
{
    int id_c= type.toInt();
    QString Id = QString::number(id_c);
    query.prepare("select * from commande where id_c=:id_c");
    query.bindValue(":id_c",Id);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date commande"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Id du client"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Ville"));
}
else if (k==3)
{
    query.prepare("select * from commande where ville=:ville");
    query.bindValue(":ville",type);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date commande"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Id du client"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Ville"));
}
        return model;
}
bool Commandes::ajoutecontenir(int id_c,int id_pr,int quantite,float prix)
{
    QSqlQuery query;
    QString id = QString::number(id_pr);
    QString id1 = QString::number(id_c);
    //QString id2 = QString::number(quantite);
    QString id3 = QString::number(prix);
    query.prepare("insert into contenir (id_pr ,id_co ,quantite ,prix)" "values (:id_pr, :id_co, :quantite, :prix)");
    query.bindValue(":id_pr",id);
    query.bindValue(":id_co",id1);
    query.bindValue(":quantite",quantite);
    query.bindValue(":prix",id3);
    return query.exec();
}
float Commandes::getPrice(int id_pr)
{
    QSqlQuery query;
     QString id = QString::number(id_pr);
    query.prepare("select * from produit where id_pr=:id_pr");
    query.bindValue(":id_pr",id);
    query.exec();
    query.first();
    return query.value(2).toFloat();
}
int Commandes::getCoupon(QString coupon)
{
     QSqlQuery query;
     query.prepare("select * from coupon where code=:coupon");
     query.bindValue(":coupon",coupon);
     query.exec();
     query.first();
     if(query.value(0).toBool()==false)
         return 0;
     else return query.value(1).toInt();
}
