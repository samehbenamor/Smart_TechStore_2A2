#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class produit
{
    QString nom_pr, qr_code, image, description, date_impo;
    float prix;
    int id_pr, stock;

public:
    //Constructeurs
        produit() {}
        produit(int, QString, float, QString, int, QString, QString, QString);

    //Getters
        //Strings
        QString getNom_pr(){return nom_pr;}
        QString getDesc(){return description;}
        QString getQr(){return qr_code;}
        QString getImage(){return image;}
        QString getDate(){return date_impo;}
        //Int
        int getIdPr(){return id_pr;}
        int getStock(){return stock;}
        //Float
        float getPrix(){return prix;}
    //Setters
        //Strings
        void setNom_pr(QString nom){nom_pr = nom;}
        void setQR(QString qr){qr_code = qr;}
        void setImage(QString im){image = im;}
        void setDesc(QString desc){description = desc;}
        void setDate(QString da){date_impo = da;}
        //Int
        void setIdPr(int id){id_pr = id;}
        void setStock(int st){stock = st;}
        //Float
        void setPrix(float pr){prix = pr;}
    //Fonctionalités de Base relatives à l'entite Produit
        bool ajouterProduit();
        QSqlQueryModel * afficher();
        bool supprimerProduit(int);


};

#endif // PRODUIT_H
