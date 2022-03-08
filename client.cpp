#include "client.h"
//  produit(int, QString, float, QString, int, QString, QString, QString);
/*QString nom_pr, qr_code, image, description, date_impo;
    float prix;
    int id_pr, stock;*/
client::client(int id_c, QString prenom, QString nom, QString address)
{
    this->id_c=id_c;
    this->prenom=prenom;
    this->nom=nom;
    this->address=address;
}
bool client::ajouterClient()
{
    QSqlQuery query;
    QString id = QString::number(id_c);

    query.prepare("insert into CLIENT (ID_C, PRENOM, NOM, ADDRESS)""values (:id, :prenom, :nom, :address)");
    //Binding
    query.bindValue(":id", id);
    query.bindValue(":prenom", prenom);
    query.bindValue(":nom", nom);
    query.bindValue(":address", address);
    return query.exec();
}

QSqlQueryModel * client::afficherClient()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_c"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("address"));
    return model;
}
bool client::supprimerClient(int id_c) {
    QSqlQuery query;
    QString id_conv = QString::number(id_c);
    query.prepare("Delete from client where ID_C= :id");
    query.bindValue(":id", id_conv);
    return query.exec();
}
QSqlQuery client::rechercherClient(int i)
{
    QSqlQuery query;
    QString Id = QString::number(i);
    query.prepare("select * from client where id_c=:id_c");
    query.bindValue(":id_c",Id);
    query.exec();
    return   query;
}

bool client::modifierClient(){
        QSqlQuery query;

QString Id = QString::number(id_c);
query.prepare("UPDATE client SET id_c=:id_c,prenom=:prenom,nom=:nom,address=:address WHERE id_c=:id_c");
       query.bindValue(":id_c",Id);
       query.bindValue(":prenom", prenom);
       query.bindValue(":nom", nom);
       query.bindValue(":address", address);
       return  query.exec();
}
