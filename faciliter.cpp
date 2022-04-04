#include "faciliter.h"
//janvier, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre;
faciliter::faciliter(int janvier, int fevrier, int mars, int avril, int mai, int juin, int juillet, int aout, int septembre, int octobre, int novembre, int decembre)
{
    this->janvier=janvier;
    this->fevrier=fevrier;
    this->mars=mars;
    this->avril=avril;
    this->mai=mai;
    this->juin=juin;
    this->juillet=juillet;
    this->aout=aout;
    this->septembre=septembre;
    this->octobre=octobre;
    this->novembre=novembre;
    this->decembre=decembre;
}

bool faciliter::ajouterFacil()
{
    QSqlQuery query;
    QString id = QString::number(janvier);

    query.prepare("insert into FACILITER (janvier, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre)""values (:janvier, :fevrier, :mars, :avril, :mai, :juin, :juillet, :aout, :septembre, :octobre, :novembre, :decembre)");
    //Binding
    query.bindValue(":janvier", id);
    query.bindValue(":fevrier", fevrier);
    query.bindValue(":mars", mars);
    query.bindValue(":avril", avril);
    query.bindValue(":mai", mai);
    query.bindValue(":juin", juin);
    query.bindValue(":juillet", juillet);
    query.bindValue(":aout", aout);
    query.bindValue(":septembre", septembre);
    query.bindValue(":octobre", octobre);
    query.bindValue(":novembre", novembre);
    query.bindValue(":decembre", decembre);
    return query.exec();
}

QSqlQueryModel * faciliter::afficherFaciliter()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from faciliter");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("janvier"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("fevrier"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("mars"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("avril"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mai"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("juin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("juillet"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("aout"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("septembre"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("octobre"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("novembre"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("decembre"));
    return model;
}
bool faciliter::supprimerFaciliter(int janvier) {
    QSqlQuery query;
    QString id_conv = QString::number(janvier);
    query.prepare("Delete from faciliter where janvier= :janvier");
    query.bindValue(":janvier", id_conv);
    return query.exec();
}
