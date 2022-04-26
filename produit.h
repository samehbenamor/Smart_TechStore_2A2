#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class produit
{

    QString nom, qr_code, image, description, date_impo;
    int id_pr, stock, prix;

public:

    //Constructeurs
        produit() {}
        produit(int, QString, int, QString, int, QString, QString,QString);

    //Getters
        //Strings
        QString getNom_pr(){return nom;}
        QString getDesc(){return description;}
        QString getQr(){return qr_code;}
        QString getImage(){return image;}
        QString getDate(){return date_impo;}
        //Int
        int getIdPr(){return id_pr;}
        int getStock(){return stock;}
        //Float
        int getPrix(){return prix;}
    //Setters
        //Strings
        void setNom_pr(QString nom2){nom = nom2;}
        void setQR(QString qr){qr_code = qr;}
        void setImage(QString im){image = im;}
        void setDesc(QString desc){description = desc;}
        void setDate(QString da){date_impo = da;}
        //Int
        void setIdPr(int id){id_pr = id;}
        void setStock(int st){stock = st;}
        //Float
        void setPrix(int pr){prix = pr;}
    //Fonctionalités de Base relatives à l'entite Produit
        bool ajouterProduit();
        QSqlQueryModel * afficher();
        bool supprimerProduit(int);
        QSqlQuery rechercherProduit(int);
        bool modifierProduit();
        QSqlQuery NbProduit();
        QSqlQuery NbProduit1000();
        QSqlQueryModel * afficherLatest();
        QSqlQueryModel * afficherRestock();
        QSqlQueryModel * afficherRecherche(QString re);
        bool UpdateQrcodeLink(QString qr, QString id);
};

#endif // PRODUIT_H
