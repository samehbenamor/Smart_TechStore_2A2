#ifndef EMPLOYEES_FONCTIONS_H
#define EMPLOYEES_FONCTIONS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



class employees_fonctions
{
public:
    employees_fonctions();
};

#endif // EMPLOYEES_FONCTIONS_H




class client
{
    QString id_c, prenom, nom, address;


public:
    //Constructeurs
        client() {}
        client(int, QString, QString, QString);

    //Getters
        //Strings
        QString getNom_c(){return nom;}
        QString getPrenom_c(){return prenom;}
        QString getAddress(){return address;}

    //Setters
        //Strings
        void setNom_pr(QString nomm){nom = nomm;}
        void setQR(QString pree){prenom = pree;}
        void setImage(QString add){address = add;}


        bool ajouterClient();
        QSqlQueryModel * afficherClient();
        bool supprimerClient(int);


};
