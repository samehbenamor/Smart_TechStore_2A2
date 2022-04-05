#include "produit.h"
//  produit(int, QString, float, QString, int, QString, QString, QString);
/*QString nom_pr, qr_code, image, description, date_impo;
    float prix;
    int id_pr, stock;*/
produit::produit(int id_pr, QString nom_pr, int prix, QString qr_code, int stock, QString image, QString date_impo, QString description)
{

    this->id_pr=id_pr;
    this->nom=nom_pr;
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
    QString idt = QString::number(id_pr);
    //QString stock_conv = QString::number(stock);
    //QString prix_conv = QString::number(prix);
    //prepare function literally prepares the request before excuting it to render it more secure, pretty damn bs if you ask me
    query.prepare("insert into PRODUIT (ID_PR, NOM, PRIX, QR_CODE, STOCK, IMAGE, DATE_IMPO, DESCRIPTION)" "values (:id, :nom_pr, :prix, :qr_code, :stock, :image, :date_impo, :description)");

    //Binding
    query.bindValue(":id", idt);
    query.bindValue(":nom_pr", nom);
    query.bindValue(":prix", prix);
    query.bindValue(":qr_code", qr_code);
    query.bindValue(":stock", stock);
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
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QR CODE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STOCK"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("IMAGE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DI"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DES"));
    return model;
}

/*QSqlQuery produit::LatestProduit() {
    QSqlQuery query;
    query.exec("SELECT * FROM produit WHERE ID_PR=(SELECT max(ID_PR) FROM produit);");
    return query;
}
*/

QSqlQueryModel * produit::afficherLatest() {
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit WHERE ID_PR=(SELECT max(ID_PR) FROM produit);");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QR CODE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STOCK"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("IMAGE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DI"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DES"));
    return model;
}

QSqlQueryModel * produit::afficherRecherche(QString re) {
    QSqlQueryModel * model=new QSqlQueryModel();

    //id_pr, nom, prix, qr_code, stock, image, date_impo, description

    model->setQuery("SELECT * FROM produit WHERE NOM LIKE '"+re+"%' OR ID_PR LIKE '"+re+"%' OR PRIX LIKE '"+re+"%' OR STOCK LIKE '"+re+"%' OR DATE_IMPO LIKE '"+re+"%' OR DESCRIPTION LIKE '"+re+"%'");
    // model->setQuery("SELECT * FROM reclamation WHERE numrec LIKE '"+recherche+"%' OR titre LIKE '"+recherche+"%' OR type LIKE '"+recherche+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QR CODE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STOCK"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("IMAGE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DI"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DES"));
    return model;
}


QSqlQueryModel * produit::afficherRestock() {
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM produit WHERE STOCK=0;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DES"));
    return model;
}

bool produit::supprimerProduit(int id) {
    QSqlQuery query;
    QString id_conv = QString::number(id);
    query.prepare("Delete from produit where ID_PR= :id");
    query.bindValue(":id", id_conv);
    return query.exec();
}
QSqlQuery produit::rechercherProduit(int i)
{

    QSqlQuery query;
    QString Id = QString::number(i);
    query.prepare("select * from produit where id_pr=:id_pr");
    query.bindValue(":id_pr",Id);
    query.exec();
    return   query;

}

bool produit::modifierProduit(){
        QSqlQuery query;

QString Id = QString::number(id_pr);
query.prepare("UPDATE PRODUIT SET NOM= :nom_pr,PRIX= :prix,QR_CODE= :qr_code,STOCK= :stock,IMAGE= :image,DATE_IMPO= :date_impo,DESCRIPTION=:description, ID_PR=:id_pr WHERE id_pr=:id_pr");
       query.bindValue(":id_pr",Id);
       query.bindValue(":nom_pr", nom);
       query.bindValue(":prix", prix);
       query.bindValue(":qr_code", qr_code);
       query.bindValue(":stock", stock);
       query.bindValue(":image", image);
       query.bindValue(":date_impo", date_impo);
       query.bindValue(":description", description);
       return  query.exec();

}
bool produit::UpdateQrcodeLink(QString qr, QString id) {
    QSqlQuery query;
    query.prepare("UPDATE PRODUIT SET QR_CODE= :qrc where id_pr= :id_pr");
    query.bindValue(":qrc", qr);
    query.bindValue(":id_pr", id);
    return query.exec();
}
QSqlQuery produit::NbProduit() {
    QSqlQuery query;
     query.exec("SELECT COUNT(*) FROM produit");
     return query;
    /*QSqlQuery query;
    query.prepare("SELECT COUNT(*) from produit");
    query.exec();
    int i = query.size();
    return i;*/
}
