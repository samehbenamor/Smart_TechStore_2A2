#include "historique.h"
#include <QDateTime>

     historique::historique()
    {
        date=QDateTime::currentDateTime();

    }
    historique:: historique(QString etat)
    {

        date=QDateTime::currentDateTime();
        this->etat=etat;

    }
    void historique::ajouter_historique()
    {
        QSqlQuery query;
        query.prepare("INSERT INTO HISTORIQUE (etat,date_historique) VALUES(:etat,:DATE_HISTORIQUE ) ");
        query.bindValue(":etat",etat);
        query.bindValue(":DATE_HISTORIQUE",date);

        query.exec();


    }
    void historique::setEtat(QString etat)
    {
        this->etat=etat;
    }

    QSqlQueryModel * historique::afficherHistorique()
    {
        QSqlQueryModel * model= new QSqlQueryModel();


            model->setQuery("select ETAT,DATE_HISTORIQUE FROM HISTORIQUE order by id_historique DESC ;");



        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ETAT"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

        return model;
}
