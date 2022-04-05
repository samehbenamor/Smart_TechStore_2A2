#include "client.h"

client::client(int id_c, QString nom, QString prenom, QString address)
{
    this->id_c=id_c;
    this->nom=nom;
    this->prenom=prenom;
    this->address=address;
}
bool client::ajouterClient()
{
    QSqlQuery query;
    query.prepare("insert into produit (id_c, nom, prenom, address)""values (:id_c, :nom, :prenom, :address");
    //Binding
    query.bindValue(":id_c", id_c);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    return query.exec();
}

QSqlQueryModel * client::afficherClient()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Prenom"));
    return model;
}
bool client::supprimerClient(int id_c) {
    QSqlQuery query;
    QString id_conv = QString::number(id_c);
    query.prepare("Delete from produit where ID_PR= :id");
    query.bindValue(":id", id_conv);
    return query.exec();
}
