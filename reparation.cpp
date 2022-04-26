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

Reparation::Reparation(int id_rep,int etat,QString date_end,QString date_start,int id_em,int id_c){
    this->id_rep=id_rep;
    this->etat=etat;
    this->date_end=date_end;
    this->date_start=date_start;
    this->id_em=id_em;
    this->id_c=id_c;
}

Reparation::Reparation(int id_rep,QString image_rep){
    this->id_rep=id_rep;
    this->image_rep=image_rep;
}


/* ******************************************************************************************************************************************************  */
/* ******************************************************************************************************************************************************  */
/* ******************************************************************************************************************************************************  */



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
/* ******************************************************************************************************************************************************  */
/* ******************************************************************************************************************************************************  */

bool Reparation::ajouter(){
    QSqlQuery query;
    QString res= QString::number(id_rep);

    //prepare() prend la requete en paramètre pour la préparer à l'exécution
    query.prepare("insert into Reparation (id_rep ,etat ,date_end ,date_start ,id_em ,id_c)"
                                  "values (:id_rep, :etat, :date_end, :date_start, :id_em, :id_c)");

    //creation des variables liées
    query.bindValue(":id_rep", res);
    query.bindValue(":etat", etat);
    //query.bindValue(":image_rep", image_rep);
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
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id Reparation"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("IMAGE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date debut"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date fin"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Id Employé"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Id Client"));

    return model;
}

/* ******************************************************************************************************************************************************  */

bool Reparation::modifier(){
        QSqlQuery query;
        QString id_rep_string=QString::number(id_rep);

query.prepare
        (" UPDATE Reparation SET id_rep=:id_rep,etat=:etat,date_end=:date_end,date_start=:date_start,id_em=:id_em,id_c=:id_c WHERE id_rep=:id_rep");

       query.bindValue(":id_rep", id_rep_string);
       query.bindValue(":etat",etat);
       query.bindValue(":date_end",date_end);
       query.bindValue(":date_start",date_start);
       query.bindValue(":id_em", id_em);
       query.bindValue(":id_c", id_c);

       return query.exec();
}

/* ******************************************************************************************************************************************************  */


QSqlQueryModel * Reparation::Recherche(int k,QString type)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery query;
if(k==1)
{
        int id_rep= type.toInt();
        QString Id = QString::number(id_rep);
        query.prepare("select * from Reparation where id_rep=:id_rep");
        query.bindValue(":id_rep",Id);
        query.exec();
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID REPARATION"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("IMAGE REPARATION"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE START"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE END"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID EMPLOYE"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID CLIENT"));
}
else if (k==2)
{
    int id_c= type.toInt();
    QString Idc = QString::number(id_c);
    query.prepare("select * from Reparation where id_c=:id_c");
    query.bindValue(":id_c",Idc);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID REPARATION"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("IMAGE REPARATION"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE START"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE END"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID EMPLOYE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID CLIENT"));}
else if (k==3)
{
    int etat= type.toInt();
    QString et = QString::number(etat);
    query.prepare("select * from Reparation where etat=:etat");
    query.bindValue(":etat",et);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID REPARATION"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("IMAGE REPARATION"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE START"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE END"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID EMPLOYE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID CLIENT"));
}
        return model;
}



/* ******************************************************************************************************************************************************  */


QSqlQueryModel * Reparation::statistic1(){
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select id_c,(count(id_c)*100/ (select count(*)from Reparation)) as pourcentage from Reparation group by id_c");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID CLIENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("pourcentage"));


    return model;
}

QSqlQueryModel * Reparation::statistic2(){
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select id_em,(count(id_em)*100/ (select count(*)from Reparation)) as pourcentage from Reparation group by id_em");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID EMPLOYE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("pourcentage"));


    return model;
}

QSqlQueryModel * Reparation::statistic3(){
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select etat,(count(etat)*100/ (select count(*)from Reparation)) as pourcentage from Reparation group by etat");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("pourcentage"));


    return model;
}


/* ******************************************************************************************************************************************************  */


bool Reparation::ajouterimage(int id_rep,QString image_rep){
    QSqlQuery query;
    QString ID_REP = QString::number(id_rep);

    query.prepare("UPDATE Reparation SET image_rep=:image_rep WHERE id_rep=:id_rep");
    query.bindValue(":id_rep", ID_REP);
    query.bindValue(":image_rep", image_rep);

    return query.exec();
}


/* ******************************************************************************************************************************************************  */
/* ******************************************************************************************************************************************************  */
