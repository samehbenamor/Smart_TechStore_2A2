#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class client
{

    QString nom, prenom, address;
    int id_c;

public:
    //Constructeurs
        client() {}
        client(int, QString, QString, QString);

    //Getters
        //Strings
        QString getNom_C(){return nom;}
        QString getPrenom(){return prenom;}
        QString getAddress(){return address;}

        //Int
        int getIdC(){return id_c;}


    //Setters
        //Strings
        void setNom_C(QString nom2){nom = nom2;}
        void setPrenom(QString pr){prenom = pr;}
        void setAddress(QString add){address = add;}

        //Int
        void setIdC(int id){id_c = id;}


        //Float


    //Fonctionalités de Base relatives à l'entite Produit
        bool ajouterClient();
        QSqlQueryModel * afficherClient();
        bool supprimerClient(int);
        QSqlQuery rechercherClient(int);
        bool modifierClient();

};

#endif // PRODUIT_H
