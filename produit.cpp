#include "produit.h"
//  produit(int, QString, float, QString, int, QString, QString, QString);
/*QString nom_pr, qr_code, image, description, date_impo;
    float prix;
    int id_pr, stock;*/
produit::produit(int id_pr, QString nom_pr, float prix, QString qr_code, int stock, QString image, QString date_impo, QString description)
{
    this->id_pr=id_pr;
    this->nom_pr=nom_pr;
    this->prix=prix;
    this->qr_code=qr_code;
    this->stock=stock;
    this->image=image;
    this->date_impo=date_impo;
    this->description=description;
}
bool produit::ajouterProduit()
{
    QSqlQuery query;
    QString id = QString::number(id_pr);
    QString stock_conv = QString::number(stock);
    QString prix_conv = QString::number(prix);
    //prepare function literally prepares the request before excuting it to render it more secure, pretty damn bs if you ask me
    query.prepare("insert into produit (id, nom_pr, prix_conv, qr_code, stock_conv, image, date_impo, description)""values (:id, :nom_pr, :prix_conv, :qr_code, :stock_conv, :image, :date_impo, :description");
    //Binding
    query.bindValue(":id", id);
    query.bindValue(":nom_pr", nom_pr);
    query.bindValue(":prix_conv", prix_conv);
    query.bindValue(":qr_code", qr_code);
    query.bindValue(":stock_conv", stock_conv);
    query.bindValue(":image", image);
    query.bindValue(":date_impo", date_impo);
    query.bindValue(":description", description);
    return query.exec();
}

QSqlQueryModel * produit::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from produit");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    //model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    //model->setHeaderData(0, Qt::Horizontal, QObject::tr("Prenom"));
    return model;
}
bool produit::supprimerProduit(int id) {
    QSqlQuery query;
    QString id_conv = QString::number(id);
    query.prepare("Delete from produit where ID_PR= :id");
    query.bindValue(":id", id_conv);
    return query.exec();
}
