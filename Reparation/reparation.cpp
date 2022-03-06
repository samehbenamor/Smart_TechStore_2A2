#include "reparation.h"
#include <QDebug>

Reparation::Reparation(int id_rep,int etat,QString image_rep,QString date_end,QString date_start,int id_em,int id_c){
    this->id_rep=id_rep;
    this->etat=etat;
    this->image_rep=image_rep;
    this->date_end=date_end;
    this->date_start=date_start;
    this->id_em=id_em;
    this->id_c=id_c;
}

bool Reparation::rechercherClients(int i){
    bool m=false;
    QSqlQuery query;
    QString Id = QString::number(i);
    query.prepare("select * from client where id_c=:id_c");
    query.bindValue(":id_c",Id);
    query.exec();
    while (query.next()) {
    qDebug() <<query.value(0);
    m=query.value(0).toBool();
    }

    return  m;
}

bool Reparation::rechercherEmploye(int e){
    bool k=false;
    QSqlQuery query;
    QString Id = QString::number(e);
    query.prepare("select * from Employee where id_em=:id_em");
    query.bindValue(":id_em",Id);
    query.exec();
    while (query.next()) {
    k=query.value(0).toBool();
    }

    return  k;
}

bool Reparation::rechercherReparation(int r){
    bool k=false;
    QSqlQuery query;
    QString Id = QString::number(r);
    query.prepare("select * from Reparation where id_rep=:id_rep");
    query.bindValue(":id_rep",Id);
    query.exec();
    while (query.next()) {
    k=query.value(0).toBool();
    }

    return  k;
}

QSqlQuery Reparation::rechercherReparation2(int i){
    QSqlQuery query;
    QString IDREP = QString::number(i);
    query.prepare("select * from Reparation where id_rep=:id_rep");
    query.bindValue(":id_rep",IDREP);
    query.exec();

    return   query;
}
/* ******************************************************************************************************************************************************  */
bool Reparation::ajouter(){
    QSqlQuery query;
    QString res= QString::number(id_rep);

    //prepare() prend la requete en paramètre pour la préparer à l'exécution
    query.prepare("insert into Reparation (id_rep ,image_rep ,etat ,date_end ,date_start ,id_em ,id_c)"
                                  "values (:id_rep, :image_rep, :etat, :date_end, :date_start, :id_em, :id_c)");

    //creation des variables liées
    query.bindValue(":id_rep", res);
    query.bindValue(":etat", etat);
    query.bindValue(":image_rep", image_rep);
    query.bindValue(":date_end",date_end);
    query.bindValue(":date_start",date_start);
    query.bindValue(":id_em",id_em);
    query.bindValue(":id_c",id_c);

    //exec() envoie la requete pour l'executer
    return query.exec();
}

/* ******************************************************************************************************************************************************  */

bool Reparation::supprimer(int id_rep){
    QSqlQuery query;
    QString ID_REP = QString::number(id_rep);

    query.prepare("Delete from Reparation where id_rep= :id_rep");
    query.bindValue(":id_rep", ID_REP);

    return query.exec();

}

/* ******************************************************************************************************************************************************  */

QSqlQueryModel * Reparation::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from Reparation");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID REPARATION"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("IMAGE REPARATION"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE START"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE END"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID EMPLOYE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID CLIENT"));

    return model;
}

/* ******************************************************************************************************************************************************  */

bool Reparation::modifier(){
        QSqlQuery query;
        QString id_rep_string=QString::number(id_rep);

query.prepare
        (" UPDATE Reparation SET id_rep=:id_rep,image_rep=:image_rep,etat=:etat,date_end=:date_end,date_start=:date_start,id_em=:id_em,id_c=:id_c WHERE id_rep=:id_rep");

       query.bindValue(":id_rep", id_rep_string);
       query.bindValue(":etat",etat);
       query.bindValue(":image_rep",image_rep);
       query.bindValue(":date_end",date_end);
       query.bindValue(":date_start",date_start);
       query.bindValue(":id_em", id_em);
       query.bindValue(":id_c", id_c);

       return query.exec();
}
