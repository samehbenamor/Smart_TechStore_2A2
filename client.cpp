#include "client.h"
//  produit(int, QString, float, QString, int, QString, QString, QString);
/*QString nom_pr, qr_code, image, description, date_impo;
    float prix;
    int id_pr, stock;*/
client::client(int id_c, QString prenom, QString nom, QString address, int points_merci)
{
    this->id_c=id_c;
    this->prenom=prenom;
    this->nom=nom;
    this->address=address;
    this->points_merci=points_merci;
}
bool client::ajouterClient()
{
    QSqlQuery query;
    QString id = QString::number(id_c);

    query.prepare("insert into CLIENT (ID_C, PRENOM, NOM, ADDRESS, POINTS_MERCI)""values (:id, :prenom, :nom, :address, :points_merci)");
    //Binding
    query.bindValue(":id", id);
    query.bindValue(":prenom", prenom);
    query.bindValue(":nom", nom);
    query.bindValue(":address", address);
    query.bindValue(":points_merci", points_merci);
    return query.exec();
}

QSqlQueryModel * client::afficherClient()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POINTS_MERCI"));
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
QSqlQuery client::NbClient() {
    QSqlQuery query;
     query.exec("SELECT COUNT(*) FROM client");
     return query;
}
QSqlQueryModel * client::afficherLatestCl() {
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM client WHERE ID_C=(SELECT max(ID_C) FROM client);");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POINTS_MERCI"));
    return model;
}

QSqlQueryModel *  client::afficherRechercheCl(QString re) {
    QSqlQueryModel * model=new QSqlQueryModel();

    //id_pr, nom, prix, qr_code, stock, image, date_impo, description

    model->setQuery("SELECT * FROM client WHERE NOM LIKE '"+re+"%' OR ID_C LIKE '"+re+"%' OR PRENOM LIKE '"+re+"%' OR ADDRESS LIKE '"+re+"%'");
    // model->setQuery("SELECT * FROM reclamation WHERE numrec LIKE '"+recherche+"%' OR titre LIKE '"+recherche+"%' OR type LIKE '"+recherche+"%'");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POINTS_MERCI"));
    return model;
}
bool client::ajouterpm(int id, int pm) {
    QString Id = QString::number(id); //conversion du l'id du nombre a QString o nhotouh f id
    QString points = QString::number(pm);
    QSqlQuery query;
    query.prepare("UPDATE client SET POINTS_MERCI=POINTS_MERCI + :pm WHERE id_c=:Id");
    query.bindValue(":Id",Id);
    query.bindValue(":pm",points);
    return query.exec(); //returne l'execution du fonction, true ken mchet, false ken memchetich w sar erreur
}
bool client::consommerpm(int id, int pm) {
    QString Id = QString::number(id);
    QString points = QString::number(pm);
    QSqlQuery query;
    query.prepare("select POINTS_MERCI from client where id_c=:id_c");
    query.bindValue(":id_c",Id);
    query.exec();
    query.first();
    int pmm =query.value(0).toInt(); //pmm include points merci d'un client du l'id
    if (pmm <= pm) {
        return false;
    }
    else {
        QSqlQuery qry;
        qry.prepare("UPDATE client SET POINTS_MERCI=POINTS_MERCI - :pm WHERE id_c=:Id");
        qry.bindValue(":Id",Id);
        qry.bindValue(":pm",points);
        qry.exec();
        return true;
    }
}
